#pragma onces

// unsigned types
using uchar  = unsigned char;
using ushort = unsigned short;
using uint   = unsigned int;
using ulong  = unsigned long long;

// singleton shortcut
#define singleton(type, name) \
  static type& name() \
    { static type name##_; return name##_; }

// reference shortcut
#define refer(fnname, varname) \
  decltype(varname)& fnname(void) { return varname; }

// getter shortcut
#define getter(fnname, ...) \
  decltype(__VA_ARGS__) fnname(void) { return __VA_ARGS__; }

// setter shortcut
#define setter(fnname, varname, ...) \
  void fnname(decltype(varname) value) { varname = __VA_ARGS__; }