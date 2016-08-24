#include <string.h>

int strstarmatch(const char *pattern, const char *filename) {
    if (!pattern || !filename)
        return -1;

    while (pattern && *filename) {
        int star = *pattern == '*';
        const char *chunk = pattern + star;
        pattern = strchr(chunk, '*');
        size_t n = pattern ? pattern - chunk : strlen(chunk);

        if (star && !n)
            return 0;

        while (memcmp(chunk, filename, n))
            if (!star || *filename++ == '\0')
                return -1;
        filename += n;
    }

    return !(pattern == NULL && *filename == '\0');
}

#ifdef WITH_TEST
#include <assert.h>

int main() {
    assert(0 != strstarmatch(NULL, "foobar"));
    assert(0 != strstarmatch("foobar", NULL));

    assert(0 != strstarmatch("FOOBAR", "foobar"));
    assert(0 != strstarmatch("foo", "foobar"));
    assert(0 != strstarmatch("bar*", "foobar"));
    assert(0 != strstarmatch("f*R", "foobar"));

    assert(0 == strstarmatch("foobar", "foobar"));
    assert(0 == strstarmatch("*", "foobar"));
    assert(0 == strstarmatch("foo*", "foobar"));
    assert(0 == strstarmatch("fo*bar", "foobar"));
    assert(0 == strstarmatch("*bar", "foobar"));
    assert(0 == strstarmatch("f*b*r", "foobar"));
    assert(0 == strstarmatch("f**b*r", "foobar"));
    assert(0 == strstarmatch("f*", "foobar"));

    assert(0 == strstarmatch("plugin/**/*.vim", "plugin/foo/bar/baz.vim"));
    assert(0 == strstarmatch("plugin/**/*.vim", "plugin/foobar.vim"));

    return 0;
}
#endif
