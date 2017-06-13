// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: helloworld.proto

#include "helloworld.grpc_cb.pb.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/once.h>

#include <grpc_cb/impl/client/client_async_call_cqtag.h>  // for ClientAsyncCallCqTag
#include <grpc_cb/impl/client/client_call_cqtag.h>        // for ClientCallCqTag
#include <grpc_cb/impl/cqueue_for_pluck.h>                // for CQueueForPluck
#include <grpc_cb/impl/proto_utils.h>                     // for Proto::Deserialize()
#include <grpc_cb/impl/server/server_reader_cqtag.h>      // for ServerReaderCqTag
#include <grpc_cb/impl/server/server_reader_writer_cqtag.h>  // for ServerReaderWriterCqTag

// package helloworld
namespace helloworld {

namespace {

const ::google::protobuf::ServiceDescriptor*
service_descriptor_Greeter = nullptr;

void AssignDesc_helloworld_2eproto() {
  // Get the file's descriptor from the pool.
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "helloworld.proto");
  GOOGLE_CHECK(file != NULL);
  service_descriptor_Greeter = file->service(0);
}  // AssignDesc_helloworld_2eproto()

GOOGLE_PROTOBUF_DECLARE_ONCE(grpc_cb_AssignDescriptors_once_);
inline void AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(
    &grpc_cb_AssignDescriptors_once_,
    &AssignDesc_helloworld_2eproto);
}

}  // namespace

namespace Greeter {  // service Greeter

static const std::string method_names[] = {
  "/helloworld.Greeter/SayHello",
};

const ::google::protobuf::ServiceDescriptor& GetServiceDescriptor() {
  AssignDescriptorsOnce();
  assert(service_descriptor_Greeter);
  return *service_descriptor_Greeter;
}

Stub::Stub(const ::grpc_cb::ChannelSptr& channel,
    const ::grpc_cb::CompletionQueueForNextSptr& cq4n_sptr)
    : ::grpc_cb::ServiceStub(channel, cq4n_sptr) {}

::grpc_cb::Status Stub::BlockingSayHello(
    const ::helloworld::HelloRequest& request,
    ::helloworld::HelloReply* response) {
  std::string req_str(request.SerializeAsString());
  const std::string& method = method_names[0];
  std::string resp_str;
  ::grpc_cb::Status status = BlockingRequest(method, req_str, resp_str);
  if (!status.ok() || !response)
    return status;
  if (response->ParseFromString(resp_str))
    return status;
  return status.InternalError("Failed to parse response.");
}

void Stub::AsyncSayHello(
    const ::helloworld::HelloRequest& request,
    const SayHelloCallback& cb,
    const ::grpc_cb::ErrorCallback& ecb) {
  ::grpc_cb::CallSptr call_sptr(MakeSharedCall(method_names[0]));
  using CqTag = ::grpc_cb::ClientAsyncCallCqTag<::helloworld::HelloReply>;
  CqTag* tag = new CqTag(call_sptr);
  tag->SetOnResponse(cb);
  tag->SetOnError(ecb);
  if (tag->Start(request)) return;
  delete tag;
  if (ecb)
    ecb(::grpc_cb::Status::InternalError("Failed to async request."));
}

Service::Service() {}

Service::~Service() {}

const std::string& Service::GetMethodName(size_t method_index) const {
  assert(method_index < GetMethodCount());
  return method_names[method_index];
}

void Service::CallMethod(
    size_t method_index, grpc_byte_buffer* request_buffer,
    const ::grpc_cb::CallSptr& call_sptr) {
  assert(method_index < GetMethodCount());
  switch (method_index) {
    case 0:
      if (!request_buffer) return;
      SayHello(*request_buffer,
          SayHello_Replier(call_sptr));
      return;
  }  // switch
  assert(false);
  (void)request_buffer;
  (void)call_sptr;
}

void Service::SayHello(
    grpc_byte_buffer& request_buffer,
    const SayHello_Replier& replier) {
  using Request = ::helloworld::HelloRequest;
  Request request;
  ::grpc_cb::Status status =
      ::grpc_cb::Proto::Deserialize(
          &request_buffer, &request, 0 /* TODO: max_message_size*/);
  if (status.ok()) {
    SayHello(request, replier);
    return;
  }
  SayHello_Replier(
      replier).ReplyError(status);
}
void Service::SayHello(
    const ::helloworld::HelloRequest& request,
    SayHello_Replier replier) {
  (void)request;
  replier.ReplyError(::grpc_cb::Status::UNIMPLEMENTED);
}

}  // namespace Greeter

}  // namespace helloworld

