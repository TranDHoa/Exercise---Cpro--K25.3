#include "Library_Mgr.h"
#include <stdio.h>
#include <string.h>


/*
 * Description: Initializes a library's resources by setting the number of books and users to zero.
 * Input: lib - A pointer to the Library structure to be initialized.
 */
void init_library(Library *lib) {
    lib->num_books = 0;
    lib->num_users = 0;
}

/*
 * Description: Adds a new book to the library.
 * Input:
 * lib - A pointer to the Library structure.
 * title - The title of the book.
 * author - The author of the book.
 * Returns: The ID of the newly added book on success, or -1 if the library is full, and -2 if the title or author is invalid.
 */
int add_book(Library *lib, const char *title, const char *author) {
    if (lib->num_books >= MAX_BOOKS) return -1;
    if (!title || !author || strlen(title) == 0 || strlen(author) == 0) return -2; // kiểm tra xem title co dang tro vao dau khong, sau do check xem chuoi co rong khong
    Book *b = &lib->books[lib->num_books];
    b->id = lib->num_books + 1;
    strncpy(b->title, title, TITLE_LEN-1);
    b->title[TITLE_LEN-1] = '\0';
    strncpy(b->author, author, AUTHOR_LEN-1);
    b->author[AUTHOR_LEN-1] = '\0';
    b->is_borrowed = 0;
    lib->num_books++;
    return b->id;
}

/*
 * Description: Edits the title and/or author of an existing book.
 * Input:
 * lib - A pointer to the Library structure.
 * book_id - The ID of the book to be edited.
 * title - The new title of the book (can be NULL).
 * author - The new author of the book (can be NULL).
 * Returns: 0 on success, or -1 if the book is not found.
 */
int edit_book(Library *lib, int book_id, const char *title, const char *author) {
    for (int i = 0; i < lib->num_books; i++) {
        if (lib->books[i].id == book_id) {
            if (title && strlen(title) > 0)
                strncpy(lib->books[i].title, title, TITLE_LEN-1);
            if (author && strlen(author) > 0)
                strncpy(lib->books[i].author, author, AUTHOR_LEN-1);
            return 0;
        }
    }
    return -1; // not found
}

/*
 * Description: Deletes a book from the library.
 * Input:
 * lib - A pointer to the Library structure.
 * book_id - The ID of the book to be deleted.
 * Returns: 0 on success, -1 if the book is not found, or -2 if the book is currently borrowed.
 */
int delete_book(Library *lib, int book_id) {
    for (int i = 0; i < lib->num_books; i++) {
        if (lib->books[i].id == book_id) {
            if (lib->books[i].is_borrowed) return -2;
            for (int j = i; j < lib->num_books - 1; j++)
                lib->books[j] = lib->books[j + 1];
            lib->num_books--;
            return 0;
        }
    }
    return -1;
}

/*
 * Description: Adds a new user to the library.
 * Input:
 * lib - A pointer to the Library structure.
 * name - The name of the user.
 * Returns: The ID of the newly added user on success, -1 if the library is full, or -2 if the name is invalid.
 */
int add_user(Library *lib, const char *name) {
    if (lib->num_users >= MAX_USERS) return -1;
    if (!name || strlen(name) == 0) return -2;
    User *u = &lib->users[lib->num_users];
    u->id = lib->num_users + 1;
    strncpy(u->name, name, NAME_LEN-1);
    u->name[NAME_LEN-1] = '\0';
    u->num_borrowed = 0;
    for (int i = 0; i < MAX_BORROWED; i++) u->borrowed_book_ids[i] = 0;
    lib->num_users++;
    return u->id;
}

/*
 * Description: Edits the name of an existing user.
 * Input:
 * lib - A pointer to the Library structure.
 * user_id - The ID of the user to be edited.
 * name - The new name of the user.
 * Returns: 0 on success, or -1 if the user is not found.
 */
int edit_user(Library *lib, int user_id, const char *name) {
    for (int i = 0; i < lib->num_users; i++) {
        if (lib->users[i].id == user_id) {
            if (name && strlen(name) > 0)
                strncpy(lib->users[i].name, name, NAME_LEN-1);
            return 0;
        }
    }
    return -1;
}

/*
 * Description: Deletes a user from the library.
 * Input:
 * lib - A pointer to the Library structure.
 * user_id - The ID of the user to be deleted.
 * Returns: 0 on success, -1 if the user is not found, or -2 if the user has borrowed books.
 */
int delete_user(Library *lib, int user_id) {
    for (int i = 0; i < lib->num_users; i++) {
        if (lib->users[i].id == user_id) {
            if (lib->users[i].num_borrowed > 0) return -2;
            for (int j = i; j < lib->num_users - 1; j++)
                lib->users[j] = lib->users[j + 1];
            lib->num_users--;
            return 0;
        }
    }
    return -1;
}

/*
 * Description: A helper function to find a book by its ID.
 * Input:
 * lib - A pointer to the Library structure.
 * book_id - The ID of the book to find.
 * Returns: A pointer to the found Book structure, or NULL if not found.
 */
static Book* find_book(Library *lib, int book_id) {
    for (int i = 0; i < lib->num_books; i++)
        if (lib->books[i].id == book_id) return &lib->books[i];
    return NULL;
}

/*
 * Description: A helper function to find a user by their ID.
 * Input:
 * lib - A pointer to the Library structure.
 * user_id - The ID of the user to find.
 * Returns: A pointer to the found User structure, or NULL if not found.
 */
static User* find_user(Library *lib, int user_id) {
    for (int i = 0; i < lib->num_users; i++)
        if (lib->users[i].id == user_id) return &lib->users[i];
    return NULL;
}

/*
 * Description: Allows a user to borrow a book.
 * Input:
 * lib - A pointer to the Library structure.
 * user_id - The ID of the user borrowing the book.
 * book_id - The ID of the book to be borrowed.
 * Returns: 0 on success, -1 if the user is not found, -2 if the book is not found, -3 if the book is already borrowed, or -4 if the user has reached their borrowing limit.
 */
int borrow_book(Library *lib, int user_id, int book_id) {
    User *u = find_user(lib, user_id);
    Book *b = find_book(lib, book_id);
    if (!u) return -1;
    if (!b) return -2;
    if (b->is_borrowed) return -3;
    if (u->num_borrowed >= MAX_BORROWED) return -4;
    b->is_borrowed = 1;
    u->borrowed_book_ids[u->num_borrowed++] = book_id;
    return 0;
}

/*
 * Description: Allows a user to return a borrowed book.
 * Input:
 * lib - A pointer to the Library structure.
 * user_id - The ID of the user returning the book.
 * book_id - The ID of the book to be returned.
 * Returns: 0 on success, -1 if the user is not found, -2 if the book is not found, or -3 if the user did not borrow the book.
 */
int return_book(Library *lib, int user_id, int book_id) {
    User *u = find_user(lib, user_id);
    Book *b = find_book(lib, book_id);
    if (!u) return -1;
    if (!b) return -2;
    int found = 0;
    for (int i = 0; i < u->num_borrowed; i++) {
        if (u->borrowed_book_ids[i] == book_id) {
            found = 1;
            for (int j = i; j < u->num_borrowed - 1; j++)
                u->borrowed_book_ids[j] = u->borrowed_book_ids[j+1];
            u->num_borrowed--;
            break;
        }
    }
    if (!found) return -3;
    b->is_borrowed = 0;
    return 0;
}

/*
 * Description: Searches for books whose titles contain a given substring and prints the matching books to the console.
 * Input:
 * lib - A pointer to the Library structure.
 * title - The substring to search for in book titles.
 * Returns: 0 if at least one book is found, or -1 if no books match the search criteria.
 */
int search_books_by_title(const Library *lib, const char *title) {
    int found = 0;
    for (int i = 0; i < lib->num_books; i++) {
        if (strstr(lib->books[i].title, title)) {
            printf("ID: %d, Tiêu đề: %s, Tác giả: %s, %s\n",
                   lib->books[i].id, lib->books[i].title, lib->books[i].author,
                   lib->books[i].is_borrowed ? "Đã mượn" : "Còn trong kho");
            found++;
        }
    }
    return found ? 0 : -1;
}

/*
 * Description: Searches for books whose authors contain a given substring and prints the matching books to the console.
 * Input:
 * lib - A pointer to the Library structure.
 * author - The substring to search for in book authors.
 * Returns: 0 if at least one book is found, or -1 if no books match the search criteria.
 */
int search_books_by_author(const Library *lib, const char *author) {
    int found = 0;
    for (int i = 0; i < lib->num_books; i++) {
        if (strstr(lib->books[i].author, author)) {
            printf("ID: %d, Tiêu đề: %s, Tác giả: %s, %s\n",
                   lib->books[i].id, lib->books[i].title, lib->books[i].author,
                   lib->books[i].is_borrowed ? "Đã mượn" : "Còn trong kho");
            found++;
        }
    }
    return found ? 0 : -1;
}

/*
 * Description: Prints a list of all books in the library that are not currently borrowed.
 * Input: lib - A pointer to the Library structure.
 */
void print_available_books(const Library *lib) {
    printf("Danh sách sách có sẵn:\n");
    for (int i = 0; i < lib->num_books; i++) {
        if (!lib->books[i].is_borrowed) {
            printf("ID: %d, Tiêu đề: %s, Tác giả: %s\n",
                lib->books[i].id, lib->books[i].title, lib->books[i].author);
        }
    }
}

/*
 * Description: Prints the information for a specific user, including their name and the IDs of the books they have borrowed.
 * Input:
 * lib - A pointer to the Library structure.
 * user_id - The ID of the user to print information for.
 */
void print_user_info(const Library *lib, int user_id) {
    const User *u = NULL;
    for (int i = 0; i < lib->num_users; i++)
        if (lib->users[i].id == user_id) {
            u = &lib->users[i]; break;
        }
    if (!u) { printf("Không tìm thấy người dùng.\n"); return; }
    printf("ID: %d, Tên: %s, Sách đã mượn: ", u->id, u->name);
    for (int i = 0; i < u->num_borrowed; i++)
        printf("%d ", u->borrowed_book_ids[i]);
    printf("\n");
}

