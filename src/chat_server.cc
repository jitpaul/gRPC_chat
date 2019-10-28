#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "chat.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using chat::StreamRequest;
using chat::Chat;
using chat::StartSessionResponse;
using chat::JoinSessionResponse;
using chat::Login;
using chat::Logout;
using chat::Message;
using chat::StreamResponse;


class ChatImpl final : public Chat::Service{	
	static std::unordered_map < std::string, std::unordered_map<std::string, ServerReaderWriter <StreamResponse, StreamRequest>* > > allStreams;
	//static std::mutex m;
	
	public:
		
    Status ChatStream(ServerContext* context, ServerReaderWriter< StreamResponse, StreamRequest>* stream) override{
		StreamRequest message;
        while (stream->Read(&message)){
			StreamResponse responseMessage;
			std::string id = "";
			std::string userName = "";
			if(message.has_startsession_request()){
				    //std::cout<<"Client Start_Session Request Received\n";
				    StartSessionResponse* start_session_response = new StartSessionResponse();
					userName = message.startsession_request().username();
			        //m.lock();
					while(true){
						id = generateRandomId();
					    if(allStreams.find(id) == allStreams.end()) break;
					}
					allStreams[id][userName] = stream;
					start_session_response->set_session_id(id);
				    responseMessage.set_allocated_startsession_response(start_session_response);
					broadcast(responseMessage,id);	
					//m.unlock();
			}
			else {
				if(message.has_joinsession_request()){
					//std::cout<<"Client Join_Session Request Received\n";
					//m.lock();
					id = message.joinsession_request().session_id();
					userName = message.joinsession_request().username();
					if(allStreams.find(id)==allStreams.end()){
						JoinSessionResponse* join_session_response = new JoinSessionResponse();
						join_session_response->set_message(id + " is not a valid session_id");
						responseMessage.set_allocated_joinsession_response(join_session_response);
					    stream->Write(responseMessage);
					}
					else if(allStreams[id].find(userName)!=allStreams[id].end()){
						JoinSessionResponse* join_session_response = new JoinSessionResponse();
						join_session_response->set_message("Username " + userName + " is already taken.");
						responseMessage.set_allocated_joinsession_response(join_session_response);
					    stream->Write(responseMessage);
					}
					else{
						Login* newLogin = new Login();
				        newLogin->set_username(userName);
				        allStreams[id][userName] = stream;					
					    responseMessage.set_allocated_login_response(newLogin);
					    broadcast(responseMessage,id);
					}
					//m.unlock();
			    }
			    else if(message.has_message_request()){
					//std::cout<<"Client New Message Request Received\n";
				    Message* newMessage = new Message();
					newMessage->set_username(message.message_request().username());
					newMessage->set_session_id(message.message_request().session_id());
					newMessage->set_message(message.message_request().message());
					id = message.message_request().session_id();
				    responseMessage.set_allocated_message_response(newMessage);
					//m.lock();
					broadcast(responseMessage,id);
					//m.unlock();
			    }
			    else if(message.has_quitsession_request()){
					//std::cout<<"Client Logout Request Received\n";
				    Logout* newLogout = new Logout();
					//m.lock();
					id = message.quitsession_request().session_id();
					userName = message.quitsession_request().username();
					allStreams[id].erase(userName);
					newLogout->set_username(message.quitsession_request().username());
					responseMessage.set_allocated_logout_response(newLogout);
					broadcast(responseMessage,id);
					//m.unlock();
			    }
				
			}	
		}
        return Status::OK;
	}
	
	
	void broadcast(StreamResponse message, std::string id){
		for(auto eachStream:allStreams[id]){
			(eachStream.second)->Write(message);
		}
	}
	
	
	std::string generateRandomId(){
		return "12345678";
	}
  
};

std::unordered_map < std::string, std::unordered_map<std::string, ServerReaderWriter <StreamResponse, StreamRequest>* > > ChatImpl::allStreams;
//std::mutex ChatImpl::m;


void RunServer() {
  std::string server_address("0.0.0.0:50051");
  ChatImpl service;
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}


int main(int argc, char** argv) {
    RunServer();
    return 0;
}