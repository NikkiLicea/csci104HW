#include "gtest/gtest.h"
#include "../bst.h"

#include <vector>
#include <iostream>

using namespace std;

void inOrder(Node* root) {
    if(!root) return;
    inOrder(root->left);
    std::cout << root->key << std::endl;
    inOrder(root->right); 
}

TEST(IsBalancedTest, IsBalancedBST) {
    //leaf nodes
    //1 3 5 7
    Node n1(1);
    Node n3(3);
    Node n5(5);
    Node n7(7);

    //2 6
    Node n2(&n1, &n3, 1);
    Node n6(&n5, &n7, 6);

    //4
    Node n4(&n2, &n6, 4);

    EXPECT_TRUE(isBalanced(&n4));
}

TEST(IsBalancedTest, AnotherIsBalancedBST) {
    //leaf nodes
    //2 7 14 20
    Node n2(2);
    Node n7(7);
    Node n14(14);
    Node n20(20);

    //5 12 16
    Node n5(nullptr, &n7, 1);
    Node n12(nullptr, &n14, 1);
    Node n16(nullptr, &n20, 16);

    //4 15
    Node n4(&n2, &n5, 4);
    Node n15(&n12, &n16, 15);

    //10
    Node n10(&n4, &n15, 7);

    EXPECT_TRUE(isBalanced(&n10));
}

TEST(IsBalancedTest, IsNotBalancedBST) {
    //leaf nodes
    //2 7 12 15
    Node n2(2);
    Node n7(7);
    Node n12(12);
    Node n15(15);
    Node n20(20);

    //4 14
    Node n4(&n2, nullptr, 4);
    Node n14(&n12, &n15, 14);

    //10
    Node n10(&n7, &n14, 10);

    //16
    Node n16(&n10, &n20, 16);

    //5
    Node n5(&n4, &n16, 5);

    EXPECT_FALSE(isBalanced(&n5));
}

TEST(IsBalancedTest, AnotherIsNotBalancedBST) {
    //leaf nodes
    //16, 45
    Node n16(16);
    Node n45(45);

    //43
    Node n43(nullptr, &n45, 43);

    //34
    Node n34(nullptr, &n43, 34);

    //49
    Node n49(&n34, nullptr, 49);

    //23
    Node n23(&n16, &n49, 23);

    //12
    Node n12(nullptr, &n23, 12);

    EXPECT_FALSE(isBalanced(&n12));
}


TEST(IsBalancedTest, AnotherIsNotBalancedBSTNew) {
    //leaf nodes
    //16, 45
    Node n16(16);
    Node n45(45);

    //43
    Node n43(&n45, nullptr, 43);

    //34
    Node n34(&n16, nullptr, 34);

    //49
    Node n49(&n34, nullptr, 49);

    //23
    Node n2(&n43, &n49, 23);

    EXPECT_FALSE(isBalanced(&n2));
}
