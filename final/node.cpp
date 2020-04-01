#include "node.h"

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return true;
}

template<typename T>
bool Compare(const Comparison &op, const T &left, const T &right) {
    bool result;
    switch (op) {
        case Comparison::Greater:
            result = right < left;
            break;
        case Comparison::GreaterOrEqual:
            result = right <= left;
            break;
        case Comparison::Less:
            result = left < right;
            break;
        case Comparison::LessOrEqual:
            result = left <= right;
            break;
        case Comparison::Equal:
            result = left == right;
            break;
        case Comparison::NotEqual:
            result = !(left == right);
            break;
        default:
            throw invalid_argument("Invalid comparison operator");
    }

    return result;
}

/***********************************
 * Implementing DateComparisonNode
 ***********************************/
DateComparisonNode::DateComparisonNode(const Comparison &op, const Date &value) : _op(op), _value(value) {}

bool DateComparisonNode::Evaluate(const Date &date, const string &value) const {
    return Compare(this->_op, date, this->_value);
}

/***********************************
 * Implementing EventComparisonNode
 ***********************************/
EventComparisonNode::EventComparisonNode(const Comparison &op, const string &value) : _op(op), _value(value) {}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    return Compare(this->_op, event, this->_value);
}

/***********************************
 * Implementing LogicalOperationNode
 ***********************************/
LogicalOperationNode::LogicalOperationNode(
        const LogicalOperation &op,
        const shared_ptr<Node> &left,
        const shared_ptr<Node> &right
) : _operation(op), _left(left), _right(right) {}

bool LogicalOperationNode::IsAnd() const {
    return this->_operation == LogicalOperation::And;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    bool l_result = this->_left->Evaluate(date, event), r_result = this->_right->Evaluate(date, event);
    return this->IsAnd() ? (l_result && r_result) : (l_result || r_result);
}
