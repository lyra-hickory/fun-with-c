int main(void) {
  // ---- type qualifiers ----
  {
    const int x = 3;
    // x = 4; <- compiler will be unhappy

    int nums[] = {20, 30};

    // -- pointed to is const --
    const int *p = nums; // cannot update *p, so nums

    p++; // okay
    // *p = 30; <- nope!

    // -- pointer is const --
    int *const const_p = nums; // now we cannot update const_p

    // const_p++; <- nope!
    *const_p = 30; // okay!

    // -- everything is const --
    const int *const every_is_const = nums;

    // every_is_const++; <- nope!
    // *every_is_const = 30; <- nope!
  }

  // -- indirect pointers --
  {
    char **p;
    p++;    // ok!
    (*p++); // ok!
  }

  {
    char **const p;
    p++;    // error!
    (*p)++; // ok!
  }

  {
    char *const *p;
    p++;    // ok!
    (*p)++; // error!
  }

  {
    char *const *const p;
    p++;    // error!
    (*p)++; // error!
  }
}
