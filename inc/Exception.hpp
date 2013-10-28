#ifndef AUTOARGS_EXCEPTION_HPP_
#define AUTOARGS_EXCEPTION_HPP_

// --- Standard Includes ---
#include <exception>
#include <memory>
#include <string>

namespace autoargs
{

class Exception : public std::exception
{
public:
  explicit Exception( const std::string& message );
  virtual ~Exception( ) throw ( );

  const char* what( ) const throw ( );

private:
  explicit Exception( const Exception& );
  Exception& operator=( const Exception& );

  std::string message;
  std::auto_ptr<bool> whatNotCalled;
};

} // namespace autoargs
#endif /* AUTOARGS_EXCEPTION_HPP_ */
