#pragma once

#include "date.h"

#include <memory>

using namespace std;

enum LogicalOperation {
    Or,
    And
};

enum Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

/**
 * Compares two items by comparison operator
 * @tparam T
 * @param Comparison op    Comparison operator
 * @param T left           Item left from comparison operator
 * @param T right          Item left from comparison operator
 * @return bool
 */
template<typename T>
bool Compare(Comparison &op, const T &left, const T &right);

/**
 * Base Node class
 */
class Node {
public:
    virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

/**
 * Node for empty Expressions
 */
class EmptyNode : public Node {
public:
    EmptyNode() {}

    bool Evaluate(const Date &date, const string &event) const override;
};

/**
 * Node for dates comparison
 */
class DateComparisonNode : public Node {
public:
    /**
     *
     * @param op
     * @param value
     */
    DateComparisonNode(const Comparison &op, const Date &value);

    /**
     * Evaluate comparison of Dates
     * @param Date date
     * @param string value
     * @return
     */
    bool Evaluate(const Date &date, const string &event) const override;

protected:
    const Comparison _op;
    const Date _value;
};

/**
 * Node for events comparison
 */
class EventComparisonNode : public Node {
public:
    /**
     * Constructor for EventComparisonNode
     * @param Comparison op
     * @param string value
     */
    EventComparisonNode(const Comparison &op, const string &value);

    /**
     * Evaluate comparison of event's strings
     * @param date
     * @param event
     * @return
     */
    bool Evaluate(const Date &date, const string &event) const override;

protected:
    const Comparison _op;
    const string _value;
};

/**
 * Node for processing logical operations
 */
class LogicalOperationNode : public Node {
public:
    /**
     * Constructor of LogicalOperationNode
     * @param LogicalOperation op
     * @param Node left
     * @param Node right
     */
    LogicalOperationNode(const LogicalOperation &op, const shared_ptr<Node> &left, const shared_ptr<Node> &right);

    /**
     * Checks is current Logical Node it AND operator
     * @return
     */
    bool IsAnd() const;

    /**
     * Evaluates logical operation between two Nodes
     * @param date
     * @param event
     * @return
     */
    bool Evaluate(const Date &date, const string &event) const override;

protected:
    LogicalOperation _operation;
    shared_ptr<const Node> _left, _right;
};