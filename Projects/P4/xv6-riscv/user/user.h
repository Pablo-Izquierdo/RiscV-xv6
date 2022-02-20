struct stat;
struct rtcdate;
typedef uint lock_t;
typedef uint cond_t;

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int clone(void(*fcn)(void*), void *arg, void*stack); //.ADD
int join(void**stack); //.ADD
/*int sleep_thread(void*cv,lock_t t);
int wakeup_thread(void *cv);*/

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);

// threads.c
int thread_create(void (*fcn)(void*), void* arg); //.ADD
int thread_join(void); //.ADD
int lock_init(lock_t* t);
void lock_acquire(lock_t* t);
void lock_release(lock_t* t);
void cv_wait(cond_t *cv, lock_t *t);
void cv_signal(cond_t *cv);
void cv_init(cond_t *cv);