#include <reg51.h>

sbit candidate1 = P1^0;
sbit candidate2 = P1^1;
sbit candidate3 = P1^2;
sbit candidate4 = P1^3;
sbit stopVotingBtn = P1^4;
sbit showResultsBtn = P1^5;
sbit showVotesBtn = P1^6;
sbit rs = P2^7;
sbit en = P1^7;
sbit r1 = P2^0;
sbit r2 = P2^1;
sbit r3 = P2^2;
sbit r4 = P2^3;
sbit c1 = P2^4;
sbit c2 = P2^5;
sbit c3 = P2^6;

// Variables to store votes
unsigned int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
unsigned char voterLog[100];
unsigned char voterCount = 0;
unsigned char enteredPassword[4];
unsigned char correctPassword[4] = {'1', '2', '3', '4'};

// Function prototypes
void delay(unsigned int ms);
void lcdCommand(unsigned char cmd);
void lcdData(unsigned char data1);
void lcdInit();
void passwordAuthentication();
void takeVotes();
void showFinalResult();
void showVoterLog();
unsigned char getKeypadInput();


void main() {
    lcdInit();
    passwordAuthentication();
    takeVotes();

    while (1) {
        if (showResultsBtn == 0) {
            showFinalResult();
            while (showResultsBtn == 0);  
        }
        if (showVotesBtn == 0) {
            showVoterLog();
            while (showVotesBtn == 0);  
        }
    }
}


void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++);
}

// LCD command function
void lcdCommand(unsigned char cmd) {
    P3 = cmd;
    rs = 0;
    en = 1;
    delay(1);
    en = 0;
}

// LCD data function
void lcdData(unsigned char data1) {
    P3 = data1;
    rs = 1;
    en = 1;
    delay(1);
    en = 0;
}

// LCD initialization
void lcdInit() {
    lcdCommand(0x38); // 8-bit mode
    lcdCommand(0x0C); // Display ON
    lcdCommand(0x06); // Increment cursor
    lcdCommand(0x01); // Clear display
}

// Password authentication
void passwordAuthentication() {
    unsigned char i;
    lcdCommand(0x80);
    lcdData('E'); lcdData('N'); lcdData('T'); lcdData('E'); lcdData('R');
    lcdData(' '); lcdData('P'); lcdData('A'); lcdData('S'); lcdData('S');
    lcdCommand(0xC0);

    for (i = 0; i < 4; i++) {
        enteredPassword[i] = getKeypadInput();
        lcdData('*');  // Mask password
    }

    for (i = 0; i < 4; i++) {
        if (enteredPassword[i] != correctPassword[i]) {
            lcdCommand(0x01);
            lcdCommand(0x80);
            lcdData('W'); lcdData('R'); lcdData('O'); lcdData('N'); lcdData('G');
            lcdData(' '); lcdData('P'); lcdData('A'); lcdData('S'); lcdData('S');
            while (1);  // Stop further execution on wrong password
        }
    }
    lcdCommand(0x01);
}

// Voting process
void takeVotes() {
    while (1) {
        lcdCommand(0x80);
        lcdData('1'); lcdData(':'); lcdData('A'); lcdData(' ');
        lcdCommand(0xC0);
        lcdData('2'); lcdData(':'); lcdData('B'); lcdData(' ');
        lcdCommand(0x88);
        lcdData('3'); lcdData(':'); lcdData('C'); lcdData(' ');
        lcdCommand(0xC8);
        lcdData('4'); lcdData(':'); lcdData('D'); lcdData(' ');

        if (candidate1 == 0) { votes1++; voterLog[voterCount++] = 'A'; while (candidate1 == 0); }
        if (candidate2 == 0) { votes2++; voterLog[voterCount++] = 'B'; while (candidate2 == 0); }
        if (candidate3 == 0) { votes3++; voterLog[voterCount++] = 'C'; while (candidate3 == 0); }
        if (candidate4 == 0) { votes4++; voterLog[voterCount++] = 'D'; while (candidate4 == 0); }

        if (stopVotingBtn == 0) {
            lcdCommand(0x01);
            lcdCommand(0x80);
            lcdData('P'); lcdData('R'); lcdData('E'); lcdData('S'); lcdData('S');
            lcdData(' '); lcdData('6'); lcdData(' '); lcdData('F'); lcdData('O'); lcdData('R');
            lcdData(' '); lcdData('R'); lcdData('E'); lcdData('S'); lcdData('U'); lcdData('L'); lcdData('T');
            lcdCommand(0xC0);
            lcdData('P'); lcdData('R'); lcdData('E'); lcdData('S'); lcdData('S');
            lcdData(' '); lcdData('7'); lcdData(' '); lcdData('T'); lcdData('O');
            lcdData(' '); lcdData('S'); lcdData('E'); lcdData('E'); lcdData(' '); lcdData('V'); lcdData('O'); lcdData('T'); lcdData('E');
            break;
        }
    }
}

// Show final voting result
void showFinalResult() {
    lcdCommand(0x01);
    lcdCommand(0x80);
    lcdData('A'); lcdData(':'); lcdData((votes1 % 10) + '0');
    lcdCommand(0xC0);
    lcdData('B'); lcdData(':'); lcdData((votes2 % 10) + '0');
    lcdCommand(0x88);
    lcdData('C'); lcdData(':'); lcdData((votes3 % 10) + '0');
    lcdCommand(0xC8);
    lcdData('D'); lcdData(':'); lcdData((votes4 % 10) + '0');
}

// Display voter log
void showVoterLog() {
    unsigned char i;
    lcdCommand(0x01);
    lcdCommand(0x80);
    lcdData('V'); lcdData('O'); lcdData('T'); lcdData('E'); lcdData('R'); lcdData('S');
    lcdCommand(0xC0);
    for (i = 0; i < voterCount && i < 16; i++) {
        lcdData(voterLog[i]);
    }
}


unsigned char getKeypadInput() {
    while (1) {
        r1 = r2 = r3 = r4 = 0;  
        c1 = c2 = c3 = 1;      

        
        r1 = r2 = r3 = r4 = 1; c1 = 0;
        if (r1 == 0) { delay(200); return '1'; }
        if (r2 == 0) { delay(200); return '4'; }
        if (r3 == 0) { delay(200); return '7'; }
        if (r4 == 0) { delay(200); return '*'; }

        
        c1 = 1; c2 = 0;
        if (r1 == 0) { delay(200); return '2'; }
        if (r2 == 0) { delay(200); return '5'; }
        if (r3 == 0) { delay(200); return '8'; }
        if (r4 == 0) { delay(200); return '0'; }

        
        c2 = 1; c3 = 0;
        if (r1 == 0) { delay(200); return '3'; }
        if (r2 == 0) { delay(200); return '6'; }
        if (r3 == 0) { delay(200); return '9'; }
        if (r4 == 0) { delay(200); return '#'; }
    }
}
