# Client API versioning versus Driver API versioning

## Compatibility SLA

The code should allow for a user to write against a different version
than the version implemented by the driver, in both forward and backward
compatible ways.

For instance, if a client code is built against version 1.1, it should
be possible to use a driver that implements 1.0 or a driver that
implements 1.2.

## Usage of the Client API

The client code never specifies a particular version in the code, such
that by a simple rebuild, the code will use the newer version of the
API, and no source code changes are necessary in order for the
developer to be able to use new features introduced by a new version
of the library.

## Versioning for Driver writers

The driver code, however, always has to target a specific version of
the API. That's a requirement because the types used by the driver
will require the driver to implement a set of methods, and those are
the only accessible features of the driver.

# How it should work

The scenario of a client using a newer driver is reasonably straight
forward, since the client just uses a subset of the published API.

The scenario of a client using an older driver, however, requires an
additional layer, which should be implemented by CxxDBI itself, to
offer wrapper classes that will implement stub methods that throw a
"not supported" exception if they are called.

## Versioned namespace

Every type introduced by CxxDBI will be in a version-specific
namespace. The current client version is aliased to the default cxxdbi
namespace.

When a new minor version is introduced, a new versioned namespace is
created, types with changes are redefined. Types with no changes are
typedef'd to the previous version namespace. If a type that didn't
change references a type that changed, that type has to be redefined
as well.

When a type is redefined in a newer version, it should extend the type
in the previous version, such that objects of the newer version are
polymorphic in code that expects the old version.

## Wrapper types with stub methods

When a driver offers an implementation with an older version than the
version being invoked by the client, a standard wrapper implementation
is transparently interjected. That wrapper will delegate the methods
defined in the previous version but stub the missing methods with a
simple "throw".
