#ifndef INCLUDED_CXXDBC_TYPE_H
#define INCLUDED_CXXDBC_TYPE_H

// standard includes
#include <iostream>

namespace cxxdbc {

enum class Type {
  // SQL type ARRAY.
  array,
  // SQL type BIGINT.
  bigint,
  // SQL type BINARY.
  binary,
  // SQL type BIT.
  bit,
  // SQL type BLOB.
  blob,
  // SQL type BOOLEAN.
  boolean,
  // SQL type CHAR.
  char_,
  // SQL type CLOB.
  clob,
  // SQL type DATALINK.
  datalink,
  // SQL type DATE.
  date,
  // SQL type DECIMAL.
  decimal,
  // SQL type DISTINCT.
  distinct,
  // SQL type DOUBLE.
  double_,
  // SQL type FLOAT.
  float_,
  // SQL type INTEGER.
  integer,
  // SQL type JAVA_OBJECT.
  java_object,
  // SQL type LONGNVARCHAR.
  longnvarchar,
  // SQL type LONGVARBINARY.
  longvarbinary,
  // SQL type LONGVARCHAR.
  longvarchar,
  // SQL type NCHAR
  nchar,
  // SQL type NCLOB.
  nclob,
  // SQL value NULL.
  null,
  // SQL type NUMERIC.
  numeric,
  // SQL type NVARCHAR.
  nvarchar,
  // SQL type is database-specific and gets mapped to a Java object that can be accessed via the
  // methods getObject and setObject.
  other,
  // SQL type REAL.
  real,
  // SQL type REF.
  ref,
  // SQL type ROWID
  rowid,
  // SQL type SMALLINT.
  smallint,
  // SQL type XML.
  sqlxml,
  // SQL type STRUCT.
  struct_,
  // SQL type TIME.
  time,
  // SQL type TIMESTAMP.
  timestamp,
  // SQL type TINYINT.
  tinyint,
  // SQL type VARBINARY.
  varbinary,
  // SQL type VARCHAR.
  varchar,
};

::std::ostream& operator<<(::std::ostream& os, Type type) {
  switch (type) {
    case Type::array: {
      os << "Type::array";
      break;
    }
    case Type::bigint: {
      os << "Type::bigint";
      break;
    }
    case Type::binary: {
      os << "Type::binary";
      break;
    }
    case Type::bit: {
      os << "Type::bit";
      break;
    }
    case Type::blob: {
      os << "Type::blob";
      break;
    }
    case Type::boolean: {
      os << "Type::boolean";
      break;
    }
    case Type::char_: {
      os << "Type::char";
      break;
    }
    case Type::clob: {
      os << "Type::clob";
      break;
    }
    case Type::datalink: {
      os << "Type::datalink";
      break;
    }
    case Type::date: {
      os << "Type::date";
      break;
    }
    case Type::decimal: {
      os << "Type::decimal";
      break;
    }
    case Type::distinct: {
      os << "Type::distinct";
      break;
    }
    case Type::double_: {
      os << "Type::double";
      break;
    }
    case Type::float_: {
      os << "Type::float";
      break;
    }
    case Type::integer: {
      os << "Type::integer";
      break;
    }
    case Type::java_object: {
      os << "Type::java_object";
      break;
    }
    case Type::longnvarchar: {
      os << "Type::longnvarchar";
      break;
    }
    case Type::longvarbinary: {
      os << "Type::longvarbinary";
      break;
    }
    case Type::longvarchar: {
      os << "Type::longvarchar";
      break;
    }
    case Type::nchar: {
      os << "Type::nchar";
      break;
    }
    case Type::nclob: {
      os << "Type::nclob";
      break;
    }
    case Type::null: {
      os << "Type::null";
      break;
    }
    case Type::numeric: {
      os << "Type::numeric";
      break;
    }
    case Type::nvarchar: {
      os << "Type::nvarchar";
      break;
    }
    case Type::other: {
      os << "Type::other";
      break;
    }
    case Type::real: {
      os << "Type::real";
      break;
    }
    case Type::ref: {
      os << "Type::ref";
      break;
    }
    case Type::rowid: {
      os << "Type::rowid";
      break;
    }
    case Type::smallint: {
      os << "Type::smallint";
      break;
    }
    case Type::sqlxml: {
      os << "Type::sqlxml";
      break;
    }
    case Type::struct_: {
      os << "Type::struct";
      break;
    }
    case Type::time: {
      os << "Type::time";
      break;
    }
    case Type::timestamp: {
      os << "Type::timestamp";
      break;
    }
    case Type::tinyint: {
      os << "Type::tinyint";
      break;
    }
    case Type::varbinary: {
      os << "Type::varbinary";
      break;
    }
    case Type::varchar: {
      os << "Type::varchar";
      break;
    }
  }

  return os;
}

}  // namespace cxxdbc

#endif  // INCLUDED_CXXDBC_TYPE_H
