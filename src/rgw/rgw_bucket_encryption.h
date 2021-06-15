// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab ft=cpp

#ifndef CEPH_RGW_BUCKET_ENCRYPTION_H
#define CEPH_RGW_BUCKET_ENCRYPTION_H

#include <string>
#include "rgw_xml.h"

class ApplyServerSideEncryptionByDefault
{
protected:
  string kmsMasterKeyID;
  string sseAlgorithm;

public:
  ApplyServerSideEncryptionByDefault(): kmsMasterKeyID(""), sseAlgorithm("") {};

  string get_kmsMasterKeyID() const {
    return kmsMasterKeyID;
  }

  string get_sseAlgorithm() const {
    return sseAlgorithm;
  }

  void encode(bufferlist& bl) const {
    ENCODE_START(1, 1, bl);
    encode(kmsMasterKeyID, bl);
    encode(sseAlgorithm, bl);
    ENCODE_FINISH(bl);
  }

  void decode(bufferlist::const_iterator& bl) {
    DECODE_START(1, bl);
    decode(kmsMasterKeyID, bl);
    decode(sseAlgorithm, bl);
    DECODE_FINISH(bl);
  }

  void decode_xml(XMLObj *obj);
  void dump_xml(Formatter *f) const;
};
WRITE_CLASS_ENCODER(ApplyServerSideEncryptionByDefault)

class ServerSideEncryptionConfiguration
{
protected:
  ApplyServerSideEncryptionByDefault applyServerSideEncryptionByDefault;
  bool bucketKeyEnabled;

public:
  ServerSideEncryptionConfiguration(): bucketKeyEnabled(false) {};

  string get_kmsMasterKeyID() const {
    return applyServerSideEncryptionByDefault.get_kmsMasterKeyID();
  }

  string get_sseAlgorithm() const {
    return applyServerSideEncryptionByDefault.get_sseAlgorithm();
  }

  bool get_bucketKeyEnabled() const {
    return bucketKeyEnabled;
  }

  void encode(bufferlist& bl) const {
    ENCODE_START(1, 1, bl);
    encode(applyServerSideEncryptionByDefault, bl);
    encode(bucketKeyEnabled, bl);
    ENCODE_FINISH(bl);
  }

  void decode(bufferlist::const_iterator& bl) {
    DECODE_START(1, bl);
    decode(applyServerSideEncryptionByDefault, bl);
    decode(bucketKeyEnabled, bl);
    DECODE_FINISH(bl);
  }

  void decode_xml(XMLObj *obj);
  void dump_xml(Formatter *f) const;
};
WRITE_CLASS_ENCODER(ServerSideEncryptionConfiguration)

class RGWBucketEncryptionConfig
{
protected:
  bool rule_exist;
  bool sse_enabled;
  ServerSideEncryptionConfiguration rule;

public:
  RGWBucketEncryptionConfig(): rule_exist(false) {}

  string get_kmsMasterKeyID() const {
    return rule.get_kmsMasterKeyID();
  }

  string get_sseAlgorithm() const {
    return rule.get_sseAlgorithm();
  }

  bool get_bucketKeyEnabled() const {
    return rule.get_bucketKeyEnabled();
  }

  bool has_rule() const {
    return rule_exist;
  }

  void encode(bufferlist& bl) const {
    ENCODE_START(1, 1, bl);
    encode(rule_exist, bl);
    if (rule_exist) {
      encode(rule, bl);
    }
    ENCODE_FINISH(bl);
  }

  void decode(bufferlist::const_iterator& bl) {
    DECODE_START(1, bl);
    decode(rule_exist, bl);
    if (rule_exist) {
      decode(rule, bl);
    }
    DECODE_FINISH(bl);
  }

  void decode_xml(XMLObj *obj);
  void dump_xml(Formatter *f) const;
};
WRITE_CLASS_ENCODER(RGWBucketEncryptionConfig)
#endif //CEPH_RGW_BUCKET_ENCRYPTION_H
