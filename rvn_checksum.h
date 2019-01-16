#ifndef RVN_CHECKSUM_H_   /* Include guard */
#define RVN_CHECKSUM_H_

/* FUNKTIONS PROTOTYPEN */
void start(void);
char* rvn_init(void);
void plott_head(char* title);
void plott_title(char* title);
void start_menu(void);
int rvn_read(char* rvn);
void rvn_checksum(char* rvn);
void rvn_print(char* rvn);
void rvn_dataOutput(char* rvn);
void SetColor(int ForgC);
void error_print(const char* errorTag, const char* errorMessage);
void green_print(const char* greenTag, const char* greenMessage);
void blue_print(const char* blueTag, const char* blueMessage);

/* KONSTANTEN */
#define RVN_SIZE 12
#define RVN_LETTER_POS 8
#define TERMINAL_COL_SIZE 100
#define CURRENT_YEAR 2019

#endif // RVN_CHECKSUM_H_
