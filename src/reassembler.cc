#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  if(data.empty()&&!is_last_substring){
    return;
  }
  else if(data.empty()&&is_last_substring){
    output_.writer().close();
    return;
  }
  uint64_t left_bd=expected_idx_;
  uint64_t right_bd=left_bd+output_.writer().available_capacity()-1;
  uint64_t last_index=first_index+data.size()-1;
  if(is_last_substring)
    iseof_=last_index+1;
  if((first_index>right_bd)||(last_index<left_bd))
      return;
  uint64_t start=max(left_bd,first_index);
  uint64_t end = min(right_bd,last_index);
  if(end<start)
    return;
  buffer_.insert({start,end,data.substr(start-first_index,end-start+1)});
  vector<interval> merge;
  auto it1=buffer_.begin();
  merge.push_back(*it1);
  ++it1;
  for(auto it=buffer_.begin();it1!=buffer_.end();++it,++it1){
    if(it1->start<=merge[merge.size()-1].end&&it1->end>=merge[merge.size()-1].end){
      merge[merge.size()-1].data=merge[merge.size()-1].data+it1->data.substr(merge[merge.size()-1].end-it1->start+1);
      merge[merge.size()-1].end=it1->end;
    }
    else if(merge[merge.size()-1].end<it1->start){
      merge.push_back(*it1);
    }
  }
  while(!merge.empty()&&merge.front().start==expected_idx_){
    output_.writer().push(merge.front().data);
    expected_idx_=merge.front().end+1;
    merge.erase(merge.begin());
  }
  buffer_.clear();
  for(auto&it:merge){
    buffer_.insert(it);
  }
  if(expected_idx_>=iseof_){
    output_.writer().close();
  }
  (void)first_index;
  (void)data;
  (void)is_last_substring;
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  uint64_t pendlen=0;
  for(auto&t:buffer_)
    pendlen+=t.end-t.start+1;
  return pendlen;
}
