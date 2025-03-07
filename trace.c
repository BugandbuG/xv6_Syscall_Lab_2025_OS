// user/trace.c
#include "kernel/types.h"
#include "user.h"
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(2, "Usage: trace mask command [args...]\n");
        exit(1);
    }

    int mask = atoi(argv[1]);  // Đọc mask từ tham số
    if (trace(mask) < 0) {
        fprintf(2, "trace failed\n");
        exit(1);
    }

    // Chạy chương trình cần trace
    exec(argv[2], &argv[2]);
    fprintf(2, "exec failed\n");
    exit(1);
}
