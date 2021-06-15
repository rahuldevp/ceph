// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab ft=cpp
//
#include "rgw_bucket_encryption.h"

void ApplyServerSideEncryptionByDefault::decode_xml(XMLObj *obj) {
  bool kmsMasterKey = RGWXMLDecoder::decode_xml("KMSMasterKeyID", kmsMasterKeyID, obj, false);
  bool sse_algo = RGWXMLDecoder::decode_xml("SSEAlgorithm", sseAlgorithm, obj, false);
  if (sseAlgorithm.compare("AES256") != 0) {
    throw RGWXMLDecoder::err("see algorithm value can only be AES256");
  }
  if ((kmsMasterKey && sse_algo) || (!kmsMasterKey && !sse_algo)) {
    throw RGWXMLDecoder::err("either KMSMasterKey or SSEAlgorithm must be specified, but not both");
  }
}

void ApplyServerSideEncryptionByDefault::dump_xml(Formatter *f) const {
  if (kmsMasterKeyID != "") {
    encode_xml("KMSMasterKeyID", kmsMasterKeyID, f);
  } else {
    encode_xml("SSEAlgorithm", sseAlgorithm, f);
  }
}

void ServerSideEncryptionConfiguration::decode_xml(XMLObj *obj) {
  RGWXMLDecoder::decode_xml("ApplyServerSideEncryptionByDefault", applyServerSideEncryptionByDefault, obj, true);
  RGWXMLDecoder::decode_xml("BucketKeyEnabled", bucketKeyEnabled, obj, false);
}

void ServerSideEncryptionConfiguration::dump_xml(Formatter *f) const {
  encode_xml("ApplyServerSideEncryptionByDefault", applyServerSideEncryptionByDefault, f);
  encode_xml("BucketKeyEnabled", bucketKeyEnabled, f);
}

void RGWBucketEncryptionConfig::decode_xml(XMLObj *obj) {
  rule_exist = RGWXMLDecoder::decode_xml("Rule", rule, obj);
  sse_enabled = false;
  if(rule.get_sseAlgorithm().compare("") != 0) {
    sse_enabled = true;
  }
}

void RGWBucketEncryptionConfig::dump_xml(Formatter *f) const {
  if (rule_exist) {
    encode_xml("Rule", rule, f);
  }
}
