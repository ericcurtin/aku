#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include <iostream>
#include <sstream>

using namespace std;

void print_trace() {
  const int max_frames = 16;
  void* array[max_frames];

  size_t size = backtrace(array, max_frames);
  char** strings = backtrace_symbols(array, size);

  Dl_info dl_info;
  for (int i = 0; i < size; ++i) {
    cout << strings[i] << '\n';
    if (dladdr(array[i], &dl_info)) {
      ostringstream oss;
      oss << "addr2line -pfC -e " << dl_info.dli_fname << ' '
          << dl_info.dli_saddr;
      system(oss.str().c_str());
    }
  }

  free(strings);
}

int main() {
  print_trace();
}
