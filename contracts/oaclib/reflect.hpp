#pragma once
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace oac {
  template<typename T>
  struct reflector {
     typedef std::false_type is_reflected;
     typedef std::false_type is_enum;
  };

} /// oac



#define OACLIB_REFLECT_VISIT_BASE(r, visitor, base) \
  oac::reflector<base>::visit( visitor );

#define OACLIB_REFLECT_VISIT2_BASE(r, visitor, base) \
  oac::reflector<base>::visit( t, forward<Visitor>(visitor) );


#define OACLIB_REFLECT_VISIT_MEMBER( r, visitor, elem ) \
{ typedef decltype((static_cast<type*>(nullptr))->elem) member_type;  \
   visitor( &type::elem ); \
}

#define OACLIB_REFLECT_VISIT2_MEMBER( r, visitor, elem ) \
{ typedef decltype((static_cast<type*>(nullptr))->elem) member_type;  \
   visitor( t.elem ); \
}


#define OACLIB_REFLECT_BASE_MEMBER_COUNT( r, OP, elem ) \
  OP oac::reflector<elem>::total_member_count

#define OACLIB_REFLECT_MEMBER_COUNT( r, OP, elem ) \
  OP 1

#define OACLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
template<typename Visitor>\
static inline void visit( Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT_MEMBER, v, MEMBERS ) \
} \
template<typename Visitor>\
static inline void visit( const type& t, Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT2_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT2_MEMBER, v, MEMBERS ) \
} \
template<typename Visitor>\
static inline void visit( type& t, Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT2_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT2_MEMBER, v, MEMBERS ) \
}

#define OACLIB_REFLECT_DERIVED_IMPL_EXT( TYPE, INHERITS, MEMBERS ) \
template<typename Visitor>\
void oac::reflector<TYPE>::visit( Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_VISIT_MEMBER, v, MEMBERS ) \
}


/**
 *  @def OACLIB_REFLECT(TYPE,MEMBERS)
 *  @brief Specializes oac::reflector for TYPE
 *
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 *
 *  @see OACLIB_REFLECT_DERIVED
 */
#define OACLIB_REFLECT( TYPE, MEMBERS ) \
    OACLIB_REFLECT_DERIVED( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define OACLIB_REFLECT_TEMPLATE( TEMPLATE_ARGS, TYPE, MEMBERS ) \
    OACLIB_REFLECT_DERIVED_TEMPLATE( TEMPLATE_ARGS, TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define OACLIB_REFLECT_EMPTY( TYPE ) \
    OACLIB_REFLECT_DERIVED( TYPE, BOOST_PP_SEQ_NIL, BOOST_PP_SEQ_NIL )


#define OACLIB_REFLECT_FWD( TYPE ) \
namespace oac { \
  template<> struct reflector<TYPE> {\
       typedef TYPE type; \
       typedef oac::true_type is_reflected; \
       enum  member_count_enum {  \
         local_member_count = BOOST_PP_SEQ_SIZE(MEMBERS), \
         total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
       }; \
       template<typename Visitor> static void visit( Visitor&& v ); \
       template<typename Visitor> static void visit( const type& t, Visitor&& v ); \
       template<typename Visitor> static void visit( type& t, Visitor&& v ); \
  }; }


#define OACLIB_REFLECT_DERIVED_IMPL( TYPE, MEMBERS ) \
    OACLIB_REFLECT_IMPL_DERIVED_EXT( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define OACLIB_REFLECT_IMPL( TYPE, MEMBERS ) \
    OACLIB_REFLECT_DERIVED_IMPL_EXT( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )



/**
 *  @def OACLIB_REFLECT_DERIVED(TYPE,INHERITS,MEMBERS)
 *
 *  @brief Specializes oac::reflector for TYPE where
 *         type inherits other reflected classes
 *
 *  @param INHERITS - a sequence of base class names (basea)(baseb)(basec)
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 */
#define OACLIB_REFLECT_DERIVED( TYPE, INHERITS, MEMBERS ) \
namespace oac {  \
template<> struct reflector<TYPE> {\
    typedef TYPE type; \
    typedef oac::true_type  is_reflected; \
    typedef oac::false_type is_enum; \
    enum  member_count_enum {  \
      local_member_count = 0  BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_MEMBER_COUNT, +, MEMBERS ),\
      total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
    }; \
    OACLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
}; }
#define OACLIB_REFLECT_DERIVED_TEMPLATE( TEMPLATE_ARGS, TYPE, INHERITS, MEMBERS ) \
namespace oac {  \
template<BOOST_PP_SEQ_ENUM(TEMPLATE_ARGS)> struct reflector<TYPE> {\
    typedef TYPE type; \
    typedef oac::true_type  is_defined; \
    typedef oac::false_type is_enum; \
    enum  member_count_enum {  \
      local_member_count = 0  BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_MEMBER_COUNT, +, MEMBERS ),\
      total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( OACLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
    }; \
    OACLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
}; }
