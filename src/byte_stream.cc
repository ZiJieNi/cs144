#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : _buf(),writer_closed(false),push_number(0),pop_number(0),capacity_(capacity){}

bool Writer::is_closed() const
{
  // Your code here.

  return writer_closed;
}

void Writer::push( string data )
{
  // Your code here.
  if(is_closed())
    return;
   uint64_t push_size=std::min(data.size(),available_capacity());
   _buf.append(data.substr(0,push_size));
   push_number+=push_size;
  return;
}

void Writer::close()
{
  // Your code here.
  writer_closed= true;
  return;

}

uint64_t Writer::available_capacity() const
{
  // Your code here.

  return (capacity_-(uint64_t)(_buf.size()));
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return push_number;
}

bool Reader::is_finished() const
{
  // Your code here.
  if(writer_closed&&_buf.empty())
    return true;
  else
    return false;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return pop_number;
}

string_view Reader::peek() const
{
//   Your code here.
//  int num;
//  if(_buf.size()==1)
//    num=1;
//  else num=2;
  if(_buf.empty())
    return{};
  return string_view(_buf) ;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  if(len>=_buf.size())
    len=_buf.size();
  if(len==0)
    return ;
  pop_number+=len;
  _buf=_buf.substr(len);
  return;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return _buf.size();
}
