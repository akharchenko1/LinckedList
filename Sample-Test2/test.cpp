#include <iostream>
#include <assert.h>
#include "pch.h"
#include"../ннно1/DoubleLinckedList.h"
#include"../ннно1/Exeptions.h"



namespace googleTests {
    const static size_t GENERATED_INTEGER_NUMBERS_NUMBER = 6;
    class LinkedListFixture : public ::testing::Test {
    protected:
        LinkedList* emptyListWithInteger;
        LinkedList* nonEmptyListWithInteger;


        void SetUp() override {
            emptyListWithInteger = new LinkedList();
            assert(emptyListWithInteger != nullptr && "Failed allocate memory");
            nonEmptyListWithInteger = new LinkedList();
            fillCertainIntegersToList(*nonEmptyListWithInteger);
        }

        void TearDown() override {
            delete emptyListWithInteger;
            delete nonEmptyListWithInteger;
        }

    public:
        static void fillCertainIntegersToList(LinkedList& list) {
            list.push_back(1);
            list.push_back(2);
            list.push_back(3);
            list.push_back(4);
            list.push_back(5);
            list.push_back(6);
        }

    };

        TEST_F(LinkedListFixture, IsEmpty) {
            EXPECT_EQ(true, emptyListWithInteger->empty());
            EXPECT_EQ(0, emptyListWithInteger->size());
        }

        TEST_F(LinkedListFixture, FrontBackMethodsInEmptyList) {
            EXPECT_THROW(emptyListWithInteger->front(), LinkedLists::LinkedListsException);
            EXPECT_THROW(emptyListWithInteger->back(), LinkedLists::LinkedListsException);
        }

        TEST_F(LinkedListFixture, IsNotEmpty) {
            EXPECT_EQ(false, nonEmptyListWithInteger->empty());
            EXPECT_EQ(GENERATED_INTEGER_NUMBERS_NUMBER, nonEmptyListWithInteger->size());
        }

        TEST_F(LinkedListFixture, IsEmptyAfterCleaning) {
        nonEmptyListWithInteger->clear();
            EXPECT_EQ(true, nonEmptyListWithInteger->empty());
            EXPECT_EQ(0, nonEmptyListWithInteger->size());
        }

        TEST_F(LinkedListFixture, FrontBackMethodsAfterCleaning) {
            nonEmptyListWithInteger->clear();
            EXPECT_THROW(nonEmptyListWithInteger->front(), LinkedLists::LinkedListsException);
            EXPECT_THROW(nonEmptyListWithInteger->back(), LinkedLists::LinkedListsException);
        }

        TEST_F(LinkedListFixture, AreListsEqual) {
            auto newListWithIntegers = new LinkedList();
            fillCertainIntegersToList(*newListWithIntegers);
            EXPECT_EQ(true, (*newListWithIntegers) == (*nonEmptyListWithInteger));
            EXPECT_EQ(false, (*newListWithIntegers) != (*nonEmptyListWithInteger));
            delete newListWithIntegers;
        }

        TEST_F(LinkedListFixture, CopyConstructor) {
            LinkedList newListWithIntegers = *nonEmptyListWithInteger;
        }

        TEST_F(LinkedListFixture, CopyAssignment) {
            auto* newListWithIntegers = new LinkedList();
            *newListWithIntegers = *nonEmptyListWithInteger;
            delete newListWithIntegers;
        }

        TEST_F(LinkedListFixture, MoveConstructor) {
            LinkedList newListWithIntegers = std::move(*nonEmptyListWithInteger);
        }

        TEST_F(LinkedListFixture, MoveAssignment) {
            auto* newListWithIntegers = new LinkedList();
            *newListWithIntegers = std::move(*nonEmptyListWithInteger);
            delete newListWithIntegers;
        }

        TEST_F(LinkedListFixture, IteratorsMethods) {
            auto newListWithIntegers = new LinkedList(*nonEmptyListWithInteger);
            LinkedList::const_iterator it1 = newListWithIntegers->cbegin();
            LinkedList::const_iterator it2 = nonEmptyListWithInteger->cbegin();
            while (it1 != newListWithIntegers->cend() && it2 != nonEmptyListWithInteger->cend()) {
                EXPECT_EQ(*it1, *it2);
                it1++;
                ++it2;
            }
            delete newListWithIntegers;
        }


        TEST_F(LinkedListFixture, MergesTwoLists) {
            fillCertainIntegersToList(*nonEmptyListWithInteger);

            auto* newListGeneratedMergeOperator = new LinkedList(
                *nonEmptyListWithInteger + *nonEmptyListWithInteger);

            LinkedList::const_iterator it1 = nonEmptyListWithInteger->cbegin();
            LinkedList::const_iterator it2 = newListGeneratedMergeOperator->cbegin();
            while (it1 != nonEmptyListWithInteger->cend() && it2 != newListGeneratedMergeOperator->cend()) {
                EXPECT_EQ(*it1, *it2);
                it1++;
                ++it2;
            }

            delete newListGeneratedMergeOperator;
        }

        TEST_F(LinkedListFixture, AddAnotherList) {
            fillCertainIntegersToList(*nonEmptyListWithInteger);

            auto* newListGeneratedMergeOperator = new LinkedList(*nonEmptyListWithInteger);
            *newListGeneratedMergeOperator += *nonEmptyListWithInteger;

            LinkedList::const_iterator it1 = nonEmptyListWithInteger->cbegin();
            LinkedList::const_iterator it2 = newListGeneratedMergeOperator->cbegin();
            while (it1 != nonEmptyListWithInteger->cend() && it2 != newListGeneratedMergeOperator->cend()) {
                EXPECT_EQ(*it1, *it2);
                it1++;
                ++it2;
            }

            delete newListGeneratedMergeOperator;
        }

        TEST_F(LinkedListFixture, FrontBackPop) {
            auto* saveOriginalList = new LinkedList(*nonEmptyListWithInteger);
            fillCertainIntegersToList(*nonEmptyListWithInteger);
            fillCertainIntegersToList(*nonEmptyListWithInteger);
            for (size_t i = 0; i < GENERATED_INTEGER_NUMBERS_NUMBER; i++) {
                nonEmptyListWithInteger->pop_back();
                nonEmptyListWithInteger->pop_front();
            }
            EXPECT_EQ(true, *saveOriginalList == *nonEmptyListWithInteger);
            EXPECT_EQ(false, *saveOriginalList != *nonEmptyListWithInteger);

            delete saveOriginalList;
        }

   
        TEST_F(LinkedListFixture, InsertRemoveMethods) {
            auto* saveOriginalList = new LinkedList(*nonEmptyListWithInteger);
            int newValue = GENERATED_INTEGER_NUMBERS_NUMBER + 1;
            LinkedList::iterator it1 = nonEmptyListWithInteger->begin();
            it1++;
            it1++;
            LinkedList::iterator it2 = nonEmptyListWithInteger->end();
            it2--;
            nonEmptyListWithInteger->insert(it1, newValue);
            nonEmptyListWithInteger->insert(nonEmptyListWithInteger->begin(), newValue);
            nonEmptyListWithInteger->insert(it2, newValue);
            nonEmptyListWithInteger->remove(newValue);

            EXPECT_EQ(true, *saveOriginalList == *nonEmptyListWithInteger);
            EXPECT_EQ(false, *saveOriginalList != *nonEmptyListWithInteger);

            delete saveOriginalList;
        }
}