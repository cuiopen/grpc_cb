// Licensed under the Apache License, Version 2.0.
// Author: Jin Qing (http://blog.csdn.net/jq0123)

#include <grpc_cb/impl/client/client_async_writer_impl.h>

#include <cassert>  // for assert()

#include <grpc_cb/channel.h>         // for MakeSharedCall()
#include <grpc_cb/impl/call_sptr.h>  // for CallSptr
#include <grpc_cb/impl/client/client_async_writer_helper.h>  // for ClientAsyncWriterHelper
#include <grpc_cb/impl/client/client_init_md_cqtag.h>  // for ClientInitMdCqTag
#include <grpc_cb/impl/client/client_writer_finish_cqtag.h>  // for ClientWriterFinishCqTag
#include <grpc_cb/status.h>                                  // for Status

namespace grpc_cb {

ClientAsyncWriterImpl::ClientAsyncWriterImpl(const ChannelSptr& channel,
                                             const std::string& method,
                                             const CompletionQueueSptr& cq_sptr)
    : cq_sptr_(cq_sptr), call_sptr_(channel->MakeSharedCall(method, *cq_sptr)) {
  assert(cq_sptr);
  assert(channel);
  ClientInitMdCqTag* tag = new ClientInitMdCqTag(call_sptr_);
  if (tag->Start()) return;
  delete tag;
  status_.SetInternalError("Failed to init client stream.");
}

bool ClientAsyncWriterImpl::Write(
    const ::google::protobuf::Message& request) {
  // XXX cache message
  return ClientAsyncWriterHelper::AsyncWrite(call_sptr_, request, status_);
}

void ClientAsyncWriterImpl::Close(const CloseHandlerSptr& handler_sptr) {
  assert(handler_sptr);
  // XXX
}

  //assert(response);
  //assert(data_sptr_);
  //Data& data = *data_sptr_;
  //assert(data.call_sptr);
  //assert(data.cq_sptr);

  //Status& status = data.status;
  //if (!status.ok()) return status;
  //ClientWriterFinishCqTag tag(data.call_sptr);
  //if (!tag.Start()) {
  //  status.SetInternalError("Failed to finish client stream.");
  //  return status;
  //}

  //data.cq_sptr->Pluck(&tag);

  //// Todo: Get trailing metadata.
  //if (tag.IsStatusOk())
  //  status = tag.GetResponse(*response);
  //else
  //  status = tag.GetStatus();

  //return status;

}  // namespace grpc_cb
