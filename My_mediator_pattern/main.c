#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declaration of classes
typedef struct User User;
typedef struct ChatRoom ChatRoom;

// Mediator interface
typedef struct {
    void (*sendMessage)(ChatRoom*, User*, const char*);
} ChatMediator;

// User class
struct User {
    const char* name;
    ChatMediator* mediator;

    // Function to send a message
    void (*sendMessage)(User*, const char*);

    // Function to receive a message
    void (*receiveMessage)(User*, const char*);
};

// ChatRoom class implementing the Mediator interface
struct ChatRoom {
    ChatMediator mediator;
    User** users;
    size_t numUsers;
};

// Function to send a message within the chatroom
void sendMessage(ChatRoom* chatRoom, User* sender, const char* message) {
    for (size_t i = 0; i < chatRoom->numUsers; ++i) {
        if (chatRoom->users[i] != sender) {
            chatRoom->users[i]->receiveMessage(chatRoom->users[i], message);
        }
    }
}

// Function to create a new User instance
User* createUser(const char* name, ChatMediator* mediator) {
    User* user = (User*)malloc(sizeof(User));
    user->name = name;
    user->mediator = mediator;
    user->sendMessage = NULL;  // Initialized in init function
    user->receiveMessage = NULL;  // Initialized in init function
    return user;
}

void sendMessageFunction(User* sender, const char* message) {
    printf("%s sends: %s\n", sender->name, message);
    sender->mediator->sendMessage((ChatRoom*)sender->mediator, sender, message);
}

void receiveMessageFunction(User* receiver, const char* message) {
    printf("%s receives: %s\n", receiver->name, message);
}

void initUser(User* user) {
    user->sendMessage = sendMessageFunction;
    user->receiveMessage = receiveMessageFunction;
}


// Function to create a new ChatRoom instance
ChatRoom* createChatRoom() {
    ChatRoom* chatRoom = (ChatRoom*)malloc(sizeof(ChatRoom));
    chatRoom->mediator.sendMessage = sendMessage;
    chatRoom->users = NULL;
    chatRoom->numUsers = 0;
    return chatRoom;
}

// Function to add a user to the chatroom
void addUserToChatRoom(ChatRoom* chatRoom, User* user) {
    chatRoom->users = realloc(chatRoom->users, (chatRoom->numUsers + 1) * sizeof(User*));
    chatRoom->users[chatRoom->numUsers++] = user;
}

// Function to free memory allocated for User and ChatRoom
void freeChatSystem(User** users, size_t numUsers, ChatRoom* chatRoom) {
    for (size_t i = 0; i < numUsers; ++i) {
        free(users[i]);
    }
    free(users);
    free(chatRoom->users);
    free(chatRoom);
}

int main() {
    // Create a chatroom
    ChatRoom* chatRoom = createChatRoom();

    // Create users and add them to the chatroom
    User* user1 = createUser("User1", (ChatMediator*)chatRoom);
    User* user2 = createUser("User2", (ChatMediator*)chatRoom);
    User* user3 = createUser("User3", (ChatMediator*)chatRoom);

    addUserToChatRoom(chatRoom, user1);
    addUserToChatRoom(chatRoom, user2);
    addUserToChatRoom(chatRoom, user3);

    // Initialize users
    initUser(user1);
    initUser(user2);
    initUser(user3);

    // Users communicate through the chatroom
    user1->sendMessage(user1, "Hello, everyone!");
    user2->sendMessage(user2, "Hi, User1!");
    user3->sendMessage(user3, "Greetings!");

    // Free the allocated memory
    freeChatSystem((User*[]){user1, user2, user3}, 3, chatRoom);

    return 0;
}
