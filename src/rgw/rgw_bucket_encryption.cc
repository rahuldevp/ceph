// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab ft=cpp
//
#include "rgw_bucket_encryption.h"
#include "rgw_xml.h"

void ApplyServerSideEncryptionByDefault::decode_xml(XMLObj *obj) {
  RGWXMLDecoder::decode_xml("KMSMasterKeyID", kmsMasterKeyID, obj, false);
  if(kmsMasterKeyID.compare("") != 0) {
    throw RGWXMLDecoder::err("implementation for KMS is not supported yet");
  }
  // TODO: need to set proper value for kmsMasterKeyID
  kmsMasterKeyID = "test-key-rahul";
  RGWXMLDecoder::decode_xml("SSEAlgorithm", sseAlgorithm, obj, false);
  if (sseAlgorithm.compare("AES256") != 0) {
    throw RGWXMLDecoder::err("sse algorithm value can only be AES256");
  }
}

void ApplyServerSideEncryptionByDefault::dump_xml(Formatter *f) const {
  // encode_xml("KMSMasterKeyID", kmsMasterKeyID, f);
  encode_xml("SSEAlgorithm", sseAlgorithm, f);
}

void ServerSideEncryptionConfiguration::decode_xml(XMLObj *obj) {
  RGWXMLDecoder::decode_xml("ApplyServerSideEncryptionByDefault", applyServerSideEncryptionByDefault, obj, true);
  // bucketKeyEnabled field is added for completion when KMS is implemented.
  RGWXMLDecoder::decode_xml("BucketKeyEnabled", bucketKeyEnabled, obj, false);
}

void ServerSideEncryptionConfiguration::dump_xml(Formatter *f) const {
  encode_xml("ApplyServerSideEncryptionByDefault", applyServerSideEncryptionByDefault, f);
  // encode_xml("BucketKeyEnabled", bucketKeyEnabled, f);
}

void RGWBucketEncryptionConfig::decode_xml(XMLObj *obj) {
  rule_exist = RGWXMLDecoder::decode_xml("Rule", rule, obj);
  if(!rule_exist) {
    throw RGWXMLDecoder::err("rule must be present in XML");
  }
}

void RGWBucketEncryptionConfig::dump_xml(Formatter *f) const {
  encode_xml("Rule", rule, f);
}
