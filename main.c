#include <stdio.h>
#include <stdlib.h>

// ---------------- Linked List for Explored Path ----------------
typedef struct Node {
    int x, y;
    struct Node* next;
} Node;

Node* createNode(int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

// ---------------- Stack for Backtracking ----------------
typedef struct Stack {
    int x, y;
    struct Stack* next;
} Stack;

Stack* top = NULL;

void push(int x, int y) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->x = x;
    newNode->y = y;
    newNode->next = top;
    top = newNode;
}

void pop(int* x, int* y) {
    if (top == NULL) return;
    Stack* temp = top;
    *x = top->x;
    *y = top->y;
    top = top->next;
    free(temp);
}

// ---------------- Queue for BFS ----------------
typedef struct Point {
    int x, y;
} Point;

typedef struct Queue {
    int front, rear, size;
    int capacity;
    Point* array;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0; 
    queue->rear = capacity - 1; 
    queue->array = (Point*)malloc(queue->capacity * sizeof(Point));
    return queue;
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int x, int y) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear].x = x;
    queue->array[queue->rear].y = y;
    queue->size++;
}

Point dequeue(Queue* queue) {
    Point p = {-1, -1}; // Default value
    if (isEmpty(queue)) return p;
    p = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return p;
}

// ---------------- Maze and Helper Structures ----------------
#define ROW 5
#define COL 5

int maze[ROW][COL];
int visited[ROW][COL] = {0};
int dx[] = {0, 0, -1, 1}; // Directions for movement
int dy[] = {-1, 1, 0, 0};

// ---------------- Function Prototypes ----------------
void displayMaze();
int isSafe(int x, int y);
void bfsSolveMaze();
void findAllPaths(int x, int y, Node* path);
void resetVisited();
void freePath(Node* path);

// ---------------- Utility Functions ----------------
void displayMaze() {
    printf("Maze:\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isSafe(int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL && maze[x][y] == 0 && !visited[x][y]);
}

void resetVisited() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            visited[i][j] = 0;
        }
    }
}

void freePath(Node* path) {
    Node* temp;
    while (path) {
        temp = path;
        path = path->next;
        free(temp);
    }
}

// ---------------- BFS SolveMaze ----------------
void bfsSolveMaze() {
    Queue* queue = createQueue(ROW * COL);
    enqueue(queue, 0, 0);
    visited[0][0] = 1;

    // Parent array to reconstruct the path
    Point parent[ROW][COL];
    parent[0][0] = (Point){-1, -1};  // Start point has no parent

    while (!isEmpty(queue)) {
        Point p = dequeue(queue);
        int x = p.x;
        int y = p.y;

        // Check if we reached the end
        if (x == ROW - 1 && y == COL - 1) {
            // Reconstruct the path
            Node* path = NULL;
            int currX = x, currY = y;

            while (currX != -1 && currY != -1) {
                Node* newNode = createNode(currX, currY);
                newNode->next = path;
                path = newNode;

                Point prev = parent[currX][currY];
                currX = prev.x;
                currY = prev.y;
            }

            // Display the path
            printf("Shortest Path using BFS:\n");
            Node* temp = path;
            while (temp) {
                printf("(%d, %d) -> ", temp->x, temp->y);
                temp = temp->next;
            }
            printf("END\n");

            // Free the path
            freePath(path);
            return;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isSafe(newX, newY)) {
                visited[newX][newY] = 1;
                enqueue(queue, newX, newY);
                parent[newX][newY] = (Point){x, y};  // Set the parent
            }
        }
    }
    printf("No path found using BFS.\n");
}

// ---------------- Find All Paths ----------------
void findAllPaths(int x, int y, Node* path) {
    if (x == ROW - 1 && y == COL - 1) {
        // Print the current path
        Node* temp = path;
        printf("Path: ");
        while (temp) {
            printf("(%d, %d) -> ", temp->x, temp->y);
            temp = temp->next;
        }
        printf("END\n");
        return;
    }

    // Explore neighbors
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (isSafe(newX, newY)) {
            visited[newX][newY] = 1;

            // Add to path
            Node* newPathNode = createNode(newX, newY);
            newPathNode->next = path;
            findAllPaths(newX, newY, newPathNode);
            // Backtrack
            visited[newX][newY] = 0;
            free(newPathNode);
        }
    }
}

// ---------------- Main Function ----------------
int main() {
    // Initialize maze (0 = path, 1 = wall)
    int tempMaze[ROW][COL] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    // Copy tempMaze to maze
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            maze[i][j] = tempMaze[i][j];
        }
    }

    displayMaze();
    resetVisited();
    printf("Finding all paths:\n");
    Node* initialPath = createNode(0, 0);
    findAllPaths(0, 0, initialPath);
    freePath(initialPath);
    
    resetVisited();
    printf("Finding shortest path using BFS:\n");
    bfsSolveMaze();

    return 0;
}