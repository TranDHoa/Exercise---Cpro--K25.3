#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Library_Mgr.h"

/*
 * Description: Prints a list of all books in the library, including their ID, title, author, and availability status.
 * Input: lib - A pointer to the Library structure.
 */
void print_books(Library *lib) {
    printf("Danh sách sách có trong thư viện:\n");
    for (int i = 0; i < lib->num_books; i++) {
        Book *b = &lib->books[i];
        printf("ID: %d, Tiêu đề: %s, Tác giả: %s, %s\n",
               b->id, b->title, b->author, b->is_borrowed ? "Đã mượn" : "Còn trong kho");
    }
}

/*
 * Description: Prints a list of all users in the library, including their ID, name, and the IDs of the books they have borrowed.
 * Input: lib - A pointer to the Library structure.
 */
void print_users(Library *lib) {
    printf("Danh sách người dùng:\n");
    for (int i = 0; i < lib->num_users; i++) {
        User *u = &lib->users[i];
        printf("ID: %d, Tên: %s, Sách đã mượn: ", u->id, u->name);
        for (int j = 0; j < u->num_borrowed; j++) {
            printf("%d ", u->borrowed_book_ids[j]);
        }
        printf("\n");
    }
}

int main() {
    Library lib;
    init_library(&lib);

    // Thêm sách
    int book1 = add_book(&lib, "Tuổi thơ dữ dội", "Phùng Quán");
    int book2 = add_book(&lib, "Dế mèn phiêu lưu ký", "Tô Hoài");
    (void)book2;    //avoid compiler warning

    // Thêm người dùng
    int user1 = add_user(&lib, "Nguyen Van A");
    int user2 = add_user(&lib, "Tran Thi B");

    printf("===============================================================================\r\n");
    // In danh sách
    print_books(&lib);
    printf("===============================================================================\r\n");
    print_users(&lib);
    printf("===============================================================================\r\n");

    // Mượn sách
    if (borrow_book(&lib, user1, book1) == 0) {
        printf("Nguyen Van A đã mượn sách Dac Nhan Tam.\n");
    }
    printf("===============================================================================\r\n");
    // Thử mượn lại sách đã được mượn
    if (borrow_book(&lib, user2, book1) != 0) {
        printf("Tran Thi B không thể mượn sách Dac Nhan Tam vì đã có người mượn.\n");
    }
    printf("===============================================================================\r\n");
    // Trả sách
    if (return_book(&lib, user1, book1) == 0) {
        printf("Nguyen Van A đã trả sách Dac Nhan Tam.\n");
    }
    printf("===============================================================================\r\n");
    // Sau khi trả, người khác có thể mượn
    if (borrow_book(&lib, user2, book1) == 0) {
        printf("Tran Thi B đã mượn sách Dac Nhan Tam.\n");
    }
    printf("===============================================================================\r\n");
    // Tìm kiếm sách theo tiêu đề
    printf("Tìm kiếm sách có tiêu đề 'Clean':\n");
    int found = search_books_by_title(&lib, "Clean");
    if (found < 0) {
        printf("Không tìm thấy sách phù hợp.\n");
    }
    printf("===============================================================================\r\n");
    // Hiển thị lại danh sách sách và người dùng
    print_books(&lib);
    printf("===============================================================================\r\n");
    print_users(&lib);
    printf("===============================================================================\r\n");
    return 0;
}