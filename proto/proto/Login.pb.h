// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/Login.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2fLogin_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_proto_2fLogin_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3015000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3015008 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_proto_2fLogin_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2fLogin_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
namespace network {
namespace packets {
class Login;
struct LoginDefaultTypeInternal;
extern LoginDefaultTypeInternal _Login_default_instance_;
}  // namespace packets
}  // namespace network
PROTOBUF_NAMESPACE_OPEN
template<> ::network::packets::Login* Arena::CreateMaybeMessage<::network::packets::Login>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace network {
namespace packets {

// ===================================================================

class Login PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:network.packets.Login) */ {
 public:
  inline Login() : Login(nullptr) {}
  virtual ~Login();
  explicit constexpr Login(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Login(const Login& from);
  Login(Login&& from) noexcept
    : Login() {
    *this = ::std::move(from);
  }

  inline Login& operator=(const Login& from) {
    CopyFrom(from);
    return *this;
  }
  inline Login& operator=(Login&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const Login& default_instance() {
    return *internal_default_instance();
  }
  static inline const Login* internal_default_instance() {
    return reinterpret_cast<const Login*>(
               &_Login_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Login& a, Login& b) {
    a.Swap(&b);
  }
  inline void Swap(Login* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Login* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Login* New() const final {
    return CreateMaybeMessage<Login>(nullptr);
  }

  Login* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Login>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const Login& from);
  void MergeFrom(const Login& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Login* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "network.packets.Login";
  }
  protected:
  explicit Login(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUserIdFieldNumber = 1,
  };
  // string UserId = 1;
  void clear_userid();
  const std::string& userid() const;
  void set_userid(const std::string& value);
  void set_userid(std::string&& value);
  void set_userid(const char* value);
  void set_userid(const char* value, size_t size);
  std::string* mutable_userid();
  std::string* release_userid();
  void set_allocated_userid(std::string* userid);
  private:
  const std::string& _internal_userid() const;
  void _internal_set_userid(const std::string& value);
  std::string* _internal_mutable_userid();
  public:

  // @@protoc_insertion_point(class_scope:network.packets.Login)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr userid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_proto_2fLogin_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Login

// string UserId = 1;
inline void Login::clear_userid() {
  userid_.ClearToEmpty();
}
inline const std::string& Login::userid() const {
  // @@protoc_insertion_point(field_get:network.packets.Login.UserId)
  return _internal_userid();
}
inline void Login::set_userid(const std::string& value) {
  _internal_set_userid(value);
  // @@protoc_insertion_point(field_set:network.packets.Login.UserId)
}
inline std::string* Login::mutable_userid() {
  // @@protoc_insertion_point(field_mutable:network.packets.Login.UserId)
  return _internal_mutable_userid();
}
inline const std::string& Login::_internal_userid() const {
  return userid_.Get();
}
inline void Login::_internal_set_userid(const std::string& value) {
  
  userid_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Login::set_userid(std::string&& value) {
  
  userid_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:network.packets.Login.UserId)
}
inline void Login::set_userid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  userid_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:network.packets.Login.UserId)
}
inline void Login::set_userid(const char* value,
    size_t size) {
  
  userid_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:network.packets.Login.UserId)
}
inline std::string* Login::_internal_mutable_userid() {
  
  return userid_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Login::release_userid() {
  // @@protoc_insertion_point(field_release:network.packets.Login.UserId)
  return userid_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Login::set_allocated_userid(std::string* userid) {
  if (userid != nullptr) {
    
  } else {
    
  }
  userid_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), userid,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:network.packets.Login.UserId)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace packets
}  // namespace network

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_proto_2fLogin_2eproto