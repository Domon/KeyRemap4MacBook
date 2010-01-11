#ifndef CALLBACKWRAPPER_HPP
#define CALLBACKWRAPPER_HPP

#include "base.hpp"
#include "KeyCode.hpp"
#include "auto_ptr.hpp"

namespace org_pqrs_KeyRemap4MacBook {
  class Params_KeyboardEventCallBack {
  public:
    // Use auto_ptr instead allocating Params_KeyboardEventCallBack in kernel stack.
    DECLARE_AUTO_PTR(Params_KeyboardEventCallBack);

    static Params_KeyboardEventCallBack* alloc(const EventType& et, const Flags& fl, const KeyCode& kc,
                                               const CharCode& cc, const CharSet& cs, const OrigCharCode& occ, const OrigCharSet& ocs,
                                               const KeyboardType& kt, bool r) {
      return new Params_KeyboardEventCallBack(et, fl, kc, cc, cs, occ, ocs, kt, r);
    }
    static Params_KeyboardEventCallBack* alloc(const EventType& et, const Flags& fl, const KeyCode& kc,
                                               const KeyboardType& kt, bool r) {
      return new Params_KeyboardEventCallBack(et, fl, kc,
                                              CharCode(0), CharSet(0), OrigCharCode(0), OrigCharSet(0),
                                              kt, r);
    }

    // ----------------------------------------
    void log(const char* message = "caught") const;
    void apply(void) const;

    EventType eventType;
    Flags flags;
    KeyCode key;
    CharCode charCode;
    CharSet charSet;
    OrigCharCode origCharCode;
    OrigCharSet origCharSet;
    KeyboardType keyboardType;
    bool repeat;

  private:
    Params_KeyboardEventCallBack(const EventType& et, const Flags& fl, const KeyCode& kc,
                                 const CharCode& cc, const CharSet& cs, const OrigCharCode& occ, const OrigCharSet& ocs,
                                 const KeyboardType& kt, bool r) :
      eventType(et), flags(fl), key(kc),
      charCode(cc), charSet(cs), origCharCode(occ), origCharSet(ocs),
      keyboardType(kt), repeat(r) {}

    static KeyboardType current_keyboardType_;
  };

  class Params_KeyboardSpecialEventCallback {
  public:
    Params_KeyboardSpecialEventCallback(const EventType& et, const Flags& fl, const ConsumerKeyCode& ckc,
                                        unsigned int fv, UInt64 g,
                                        bool r) :
      eventType(et), flags(fl), key(ckc),
      flavor(fv), guid(g),
      repeat(r) {}

    Params_KeyboardSpecialEventCallback(const EventType& et, const Flags& fl, const ConsumerKeyCode& ckc,
                                        bool r) :
      eventType(et), flags(fl), key(ckc),
      flavor(ckc.get()), guid(static_cast<UInt64>(-1)),
      repeat(r) {}

    // ----------------------------------------
    void log(const char* message = "caught") const;
    void apply(void) const;

    EventType eventType;
    Flags flags;
    ConsumerKeyCode key;
    unsigned int flavor;
    UInt64 guid;
    bool repeat;
  };

  class Params_RelativePointerEventCallback {
  public:
    Params_RelativePointerEventCallback(const Buttons& bt, int x, int y) : buttons(bt), dx(x), dy(y) {}

    void log(const char* message = "caught") const;
    void apply(void) const;

    Buttons buttons;
    int dx;
    int dy;
  };
  class Params_ScrollWheelEventCallback {
  public:
    Params_ScrollWheelEventCallback(short da1, short da2, short da3,
                                    IOFixed fd1, IOFixed fd2, IOFixed fd3,
                                    SInt32 pd1, SInt32 pd2, SInt32 pd3,
                                    SInt32 op) :
      deltaAxis1(da1), deltaAxis2(da2), deltaAxis3(da3),
      fixedDelta1(fd1), fixedDelta2(fd2), fixedDelta3(fd3),
      pointDelta1(pd1), pointDelta2(pd2), pointDelta3(pd3),
      options(op) {}

    void log(const char* message = "caught") const;
    void apply(void) const;

    short deltaAxis1;
    short deltaAxis2;
    short deltaAxis3;
    IOFixed fixedDelta1;
    IOFixed fixedDelta2;
    IOFixed fixedDelta3;
    SInt32 pointDelta1;
    SInt32 pointDelta2;
    SInt32 pointDelta3;
    SInt32 options;
  };
}

#endif
