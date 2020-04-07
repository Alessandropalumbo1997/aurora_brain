// Generated by gencpp from file brain/hormone_msg.msg
// DO NOT EDIT!


#ifndef BRAIN_MESSAGE_HORMONE_MSG_H
#define BRAIN_MESSAGE_HORMONE_MSG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace brain
{
template <class ContainerAllocator>
struct hormone_msg_
{
  typedef hormone_msg_<ContainerAllocator> Type;

  hormone_msg_()
    : name()
    , value(0)  {
    }
  hormone_msg_(const ContainerAllocator& _alloc)
    : name(_alloc)
    , value(0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  _name_type name;

   typedef int32_t _value_type;
  _value_type value;





  typedef boost::shared_ptr< ::brain::hormone_msg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::brain::hormone_msg_<ContainerAllocator> const> ConstPtr;

}; // struct hormone_msg_

typedef ::brain::hormone_msg_<std::allocator<void> > hormone_msg;

typedef boost::shared_ptr< ::brain::hormone_msg > hormone_msgPtr;
typedef boost::shared_ptr< ::brain::hormone_msg const> hormone_msgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::brain::hormone_msg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::brain::hormone_msg_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::brain::hormone_msg_<ContainerAllocator1> & lhs, const ::brain::hormone_msg_<ContainerAllocator2> & rhs)
{
  return lhs.name == rhs.name &&
    lhs.value == rhs.value;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::brain::hormone_msg_<ContainerAllocator1> & lhs, const ::brain::hormone_msg_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace brain

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::brain::hormone_msg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::brain::hormone_msg_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::brain::hormone_msg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::brain::hormone_msg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::brain::hormone_msg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::brain::hormone_msg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::brain::hormone_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "65fedc7a0cbfb8db035e46194a350bf1";
  }

  static const char* value(const ::brain::hormone_msg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x65fedc7a0cbfb8dbULL;
  static const uint64_t static_value2 = 0x035e46194a350bf1ULL;
};

template<class ContainerAllocator>
struct DataType< ::brain::hormone_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "brain/hormone_msg";
  }

  static const char* value(const ::brain::hormone_msg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::brain::hormone_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string name\n"
"int32 value\n"
;
  }

  static const char* value(const ::brain::hormone_msg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::brain::hormone_msg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.name);
      stream.next(m.value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct hormone_msg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::brain::hormone_msg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::brain::hormone_msg_<ContainerAllocator>& v)
  {
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
    s << indent << "value: ";
    Printer<int32_t>::stream(s, indent + "  ", v.value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BRAIN_MESSAGE_HORMONE_MSG_H
