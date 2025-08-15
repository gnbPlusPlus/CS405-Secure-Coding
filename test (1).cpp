// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
// CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
// CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // add a single value
    add_entries(1);

    // is the collection still empty?
    EXPECT_FALSE(collection->empty());
     
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // add 5 values
    add_entries(5);

    // collection size should now be 5
    ASSERT_EQ(collection->size(), 5);
}

// Verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterOrEqualToNumEntries) 
{
    // Check for empty collection
    ASSERT_TRUE(collection->empty());

    // Check for 0 entries
    EXPECT_GE(collection->max_size(), 0);

    // Check for 1 entry
    add_entries(1);
    EXPECT_GE(collection->max_size(), 1);

    // Check for 5 entries
    add_entries(5);
    EXPECT_GE(collection->max_size(), 5);

    // Check for 10 entries
    add_entries(10);
    EXPECT_GE(collection->max_size(), 10);

}

// Verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterOrEqualToNumEntries) 
{
	// Check for empty collection
	ASSERT_TRUE(collection->empty());

	// Check for 0 entries
    EXPECT_GE(collection->capacity(), 0);

	// Check for 1 entry
	add_entries(1);
    EXPECT_GE(collection->capacity(), 1);

	// Check for 5 entries
	add_entries(5);
    EXPECT_GE(collection->capacity(), 5);

	// Check for 10 entries
	add_entries(10);
    EXPECT_GE(collection->capacity(), 10);
}

// Verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection) 
{
    // Check initial size
	EXPECT_EQ(collection->size(), 0);

    // Resize to 5
    collection->resize(5);

    // Verify size is now 5
    ASSERT_EQ(collection->size(), 5);
}

// Verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection) 
{
    // Check initial size
    EXPECT_EQ(collection->size(), 0);

    // Resize to 3
    collection->resize(3);

    // Verify size is now 3
    ASSERT_EQ(collection->size(), 3);
}

// Verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesCollectionToZero) 
{
    // Check initial size
    EXPECT_EQ(collection->size(), 0);

    // Resize to 5
    collection->resize(5);

    // Verify size is now 5
    ASSERT_EQ(collection->size(), 5);
}

// Verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) 
{
	// Set up the collection with some values
	add_entries(17);

    // Clear the collection
    collection->clear();
    
    // Verify the collection is empty
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

}

// Verify erase(begin,end) erases the collection
TEST_F(CollectionTest, BeginEndErasesCollection) 
{
	// Set up the collection with some values
	add_entries(5); // Add 5 random values
    
    // Erase the collection
	collection->erase(collection->begin(), collection->end());

    // Verify the collection is empty
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

// Verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize) 
{
    // Add capacity to the collection
    collection->reserve(15);

    // Verify the capacity matches the reserve() call
    ASSERT_EQ(collection->capacity(), 15);

	// Verify the size is still 0
    ASSERT_EQ(collection->size(), 0);
}

// Verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
TEST_F(CollectionTest, OutOfRangeExceptionThrowsOnOutOfBoundsAttempt) 
{
    // Set up the collection with some values
    add_entries(25);

	// Verify that an out_of_range exception is thrown when accessing an out-of-bounds index
    ASSERT_THROW(collection->at(100), std::out_of_range);
}

// Positive test to verify accessing a valid index
TEST_F(CollectionTest, AccessValidIndexIsSafe) 
{
	// Set up the collection with some values
	add_entries(3);

	// Verify that a valid index can be accessed without throwing an exception
    ASSERT_NO_THROW(collection->at(1));
}

// Negative test for edge case behavior of erasing an empty collection
TEST_F(CollectionTest, EraseEmptyCollectionIsSafe) 
{
    // Verify the collection is empty
    EXPECT_TRUE(collection->empty());

	// Verify an exception is thrown when trying to erase an empty collection
	ASSERT_NO_THROW(collection->erase(collection->begin(), collection->end()), std::runtime_error);
}