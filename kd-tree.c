#include <stdio.h>
#include <stdlib.h>

/* Structure to represent a 2D point */
struct Point {
    int x, y;
};

/* Structure for k-d tree node */
struct Node {
    struct Point point;
    struct Node* left;
    struct Node* right;
    int depth;
};

/* Function to create a new k-d tree node */
struct Node* createNode(struct Point point, int depth) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->point = point;
    node->left = NULL;
    node->right = NULL;
    node->depth = depth;
    return node;
}

/* Function to build a k-d tree recursively */
struct Node* buildKdTree(struct Point* points, int n, int depth) {
    if (n == 0) {
        return NULL;
    }

    int axis = depth % 2;
    int medianIndex = n / 2;
    struct Point* medianPoint = &points[medianIndex];

    // Sort points along the current axis
    for (int i = 0; i < n; i++) {
        if (axis == 0) {
            if (points[i].x < medianPoint->x) {
                // Swap points
                struct Point temp = points[i];
                points[i] = points[medianIndex];
                points[medianIndex] = temp;
                medianIndex = i;
            }
        } else {
            if (points[i].y < medianPoint->y) {
                // Swap points
                struct Point temp = points[i];
                points[i] = points[medianIndex];
                points[medianIndex] = temp;
                medianIndex = i;
            }
        }
    }

    struct Node* node = createNode(*medianPoint, depth);
    node->left = buildKdTree(points, medianIndex, depth + 1);
    node->right = buildKdTree(points + medianIndex + 1, n - medianIndex - 1, depth + 1);

    return node;
}

/* Function to print k-d tree nodes */
void printKdTree(struct Node* node, const char* indent) {
    if (node == NULL) {
        return;
    }

    printf("%sPoint: (%d, %d) Depth: %d\n", indent, node->point.x, node->point.y, node->depth);
    printKdTree(node->left, strcat(indent, "  "));
    printKdTree(node->right, strcat(indent, "  "));
}

int main() {
    // Example points in 2D space
    struct Point points[] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}};
    int numPoints = sizeof(points) / sizeof(points[0]);

    struct Node* root = buildKdTree(points, numPoints, 0);

    printf("Constructed k-d tree:\n");
    printKdTree(root, "");

    return 0;
}