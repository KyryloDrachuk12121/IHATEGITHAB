#include "point.h"
#include <gtest/gtest.h>

TEST(PointTest, CreatePoint) {
    PointPtr p = create_point(1, 2);
    ASSERT_NE(p, nullptr); 
    EXPECT_EQ(p->x, 1);  
    EXPECT_EQ(p->y, 2);  
    destroy_point(p);      
}

TEST(PointTest, DestroyPoint) {
    PointPtr p = create_point(3, 4);
    ASSERT_NE(p, nullptr); 
    destroy_point(p);      

}


TEST(PointTest, ComparePoints_SamePoint) {
    PointPtr p1 = create_point(1, 2);
    EXPECT_EQ(compare_points(&p1, &p1), 0);
    destroy_point(p1);
}

TEST(PointTest, ComparePoints_DifferentY) {
    PointPtr p1 = create_point(1, 2);
    PointPtr p2 = create_point(1, 3);
    EXPECT_LT(compare_points(&p1, &p2), 0); 
    EXPECT_GT(compare_points(&p2, &p1), 0); 
    destroy_point(p1);
    destroy_point(p2);
}

TEST(PointTest, ComparePoints_SameYDifferentX) {
    PointPtr p1 = create_point(1, 2);
    PointPtr p2 = create_point(3, 2);
    EXPECT_LT(compare_points(&p1, &p2), 0); 
    EXPECT_GT(compare_points(&p2, &p1), 0); 
    destroy_point(p1);
    destroy_point(p2);
}


TEST(PointTest, SlopeTo_HorizontalLine) {
    PointPtr p1 = create_point(1, 2);
    PointPtr p2 = create_point(3, 2);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 0.0); 
    destroy_point(p1);
    destroy_point(p2);
}

TEST(PointTest, SlopeTo_VerticalLine) {
    PointPtr p1 = create_point(1, 2);
    PointPtr p2 = create_point(1, 4);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 1.0 / 0.0); 
    destroy_point(p1);
    destroy_point(p2);
}

TEST(PointTest, SlopeTo_SamePoint) {
    PointPtr p1 = create_point(1, 2);
    EXPECT_DOUBLE_EQ(slope_to(p1, p1), -1.0 / 0.0); 
    destroy_point(p1);
}

TEST(PointTest, SlopeTo_PositiveSlope) {
    PointPtr p1 = create_point(1, 1);
    PointPtr p2 = create_point(2, 2);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 1.0);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(PointTest, SlopeTo_NegativeSlope) {
    PointPtr p1 = create_point(1, 2);
    PointPtr p2 = create_point(2, 1);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), -1.0);
    destroy_point(p1);
    destroy_point(p2);
}


TEST(PointTest, MixedTest_CreateCompareSlope) {
    PointPtr p1 = create_point(1, 1);
    PointPtr p2 = create_point(2, 2);
    PointPtr p3 = create_point(1, 2);

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p3, nullptr);
    EXPECT_LT(compare_points(&p1, &p2), 0); 
    EXPECT_GT(compare_points(&p2, &p1), 0); 
    EXPECT_LT(compare_points(&p1, &p3), 0); 
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 1.0); 
    EXPECT_DOUBLE_EQ(slope_to(p1, p3), 1.0 / 0.0); 

    destroy_point(p1);
    destroy_point(p2);
    destroy_point(p3);
}

TEST(PointTest, MixedTest_CollinearPoints) {
    PointPtr p1 = create_point(1, 1);
    PointPtr p2 = create_point(2, 2);
    PointPtr p3 = create_point(3, 3);

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p3, nullptr);

    EXPECT_DOUBLE_EQ(slope_to(p1, p2), slope_to(p1, p3)); 
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 1.0);
    destroy_point(p1);
    destroy_point(p2);
    destroy_point(p3);
}

TEST(PointTest, MixedTest_NonCollinearPoints) {
    PointPtr p1 = create_point(1, 1);
    PointPtr p2 = create_point(2, 2);
    PointPtr p3 = create_point(1, 3);

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p3, nullptr);

    EXPECT_NE(slope_to(p1, p2), slope_to(p1, p3)); 

    destroy_point(p1);
    destroy_point(p2);
    destroy_point(p3);
}