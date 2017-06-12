// Copyright 2004 The RE2 Authors.  All Rights Reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "re2/stringpiece.h"

#include <ostream>

#include "util/util.h"

namespace re2 {

const re2::StringPiece::size_type npos = static_cast<StringPiece::size_type>(-1);

StringPiece::size_type StringPiece::copy(char* buf, size_type n,
                                         size_type pos) const {
  size_type ret = std::min(size_ - pos, n);
  memcpy(buf, data_ + pos, ret);
  return ret;
}

StringPiece StringPiece::substr(size_type pos, size_type n) const {
  if (pos > size_) pos = size_;
  if (n > size_ - pos) n = size_ - pos;
  return StringPiece(data_ + pos, n);
}

StringPiece::size_type StringPiece::find(const StringPiece& s,
                                         size_type pos) const {
  if (pos > size_) return -1;
  const_pointer result = std::search(data_ + pos, data_ + size_,
                                     s.data_, s.data_ + s.size_);
  size_type xpos = result - data_;
  return xpos + s.size_ <= size_ ? xpos : -1;
}

StringPiece::size_type StringPiece::find(char c, size_type pos) const {
  if (size_ <= 0 || pos >= size_) return -1;
  const_pointer result = std::find(data_ + pos, data_ + size_, c);
  return result != data_ + size_ ? result - data_ : -1;
}

StringPiece::size_type StringPiece::rfind(const StringPiece& s,
                                          size_type pos) const {
  if (size_ < s.size_) return -1;
  if (s.size_ == 0) return std::min(size_, pos);
  const_pointer last = data_ + std::min(size_ - s.size_, pos) + s.size_;
  const_pointer result = std::find_end(data_, last, s.data_, s.data_ + s.size_);
  return result != last ? result - data_ : -1;
}

StringPiece::size_type StringPiece::rfind(char c, size_type pos) const {
  if (size_ <= 0) return -1;
  for (size_t i = std::min(pos + 1, size_); i != 0;) {
    if (data_[--i] == c) return i;
  }
  return -1;
}

std::ostream& operator<<(std::ostream& o, const StringPiece& p) {
  o.write(p.data(), p.size());
  return o;
}

}  // namespace re2
