// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: chat.proto
#ifndef GRPC_chat_2eproto__INCLUDED
#define GRPC_chat_2eproto__INCLUDED

#include "chat.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace chat {

class Chat final {
 public:
  static constexpr char const* service_full_name() {
    return "chat.Chat";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>> ChatStream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>>(ChatStreamRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>> AsyncChatStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>>(AsyncChatStreamRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>> PrepareAsyncChatStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>>(PrepareAsyncChatStreamRaw(context, cq));
    }
  private:
    virtual ::grpc::ClientReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>* ChatStreamRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>* AsyncChatStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::chat::StreamRequest, ::chat::StreamResponse>* PrepareAsyncChatStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    std::unique_ptr< ::grpc::ClientReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>> ChatStream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>>(ChatStreamRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>> AsyncChatStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>>(AsyncChatStreamRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>> PrepareAsyncChatStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>>(PrepareAsyncChatStreamRaw(context, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>* ChatStreamRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>* AsyncChatStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::chat::StreamRequest, ::chat::StreamResponse>* PrepareAsyncChatStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_ChatStream_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status ChatStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chat::StreamResponse, ::chat::StreamRequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_ChatStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_ChatStream() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_ChatStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ChatStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chat::StreamResponse, ::chat::StreamRequest>* stream) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestChatStream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::chat::StreamResponse, ::chat::StreamRequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_ChatStream<Service > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_ChatStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_ChatStream() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_ChatStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ChatStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chat::StreamResponse, ::chat::StreamRequest>* stream) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace chat


#endif  // GRPC_chat_2eproto__INCLUDED
