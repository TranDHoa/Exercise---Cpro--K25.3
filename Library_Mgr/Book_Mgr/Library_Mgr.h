#ifndef __LIBRARY_MGR_H__
#define __LIBRARY_MGR_H__

#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_BORROWED 10
#define TITLE_LEN 100
#define AUTHOR_LEN 100
#define NAME_LEN 100

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int is_borrowed; // 0: available, 1: borrowed
} Book;

typedef struct {
    int id;
    char name[NAME_LEN];
    int borrowed_book_ids[MAX_BORROWED];
    int num_borrowed;
} User;

typedef struct {
    Book books[MAX_BOOKS];
    int num_books;
    User users[MAX_USERS];
    int num_users;
} Library;

// Khởi tạo thư viện
void init_library(Library *lib);

// Quản lý sách
int add_book(Library *lib, const char *title, const char *author);
int edit_book(Library *lib, int book_id, const char *title, const char *author);
int delete_book(Library *lib, int book_id);

// Quản lý người dùng
int add_user(Library *lib, const char *name);
int edit_user(Library *lib, int user_id, const char *name);
int delete_user(Library *lib, int user_id);

// Quản lý mượn/trả sách
int borrow_book(Library *lib, int user_id, int book_id);
int return_book(Library *lib, int user_id, int book_id);

// Tìm kiếm & hiển thị
int search_books_by_title(const Library *lib, const char *title);
int search_books_by_author(const Library *lib, const char *author);
void print_available_books(const Library *lib);
void print_user_info(const Library *lib, int user_id);

#endif // __LIBRARY_MGR_H__
