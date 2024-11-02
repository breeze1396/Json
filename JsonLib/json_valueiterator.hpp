#ifndef JSON_VALUEITERATOR_HPP
#define JSON_VALUEITERATOR_HPP

#include <iterator>
#include "json_value.hpp"

namespace bre {

// ���� ValueIterator ģ����
template<typename ValueType>
class ValueIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = ValueType*;
    using reference = ValueType&;

    // Ĭ�Ϲ��캯��
    ValueIterator() = default;

    // ���캯�������������͵ĵ�����
    ValueIterator(typename Value::Array::iterator arrayIt)
        : arrayIterator_(arrayIt), isObject_(false) {}

    // ���캯�����ڶ������͵ĵ�����
    ValueIterator(typename Value::Object::iterator objectIt)
        : objectIterator_(objectIt), isObject_(true) {}

    // ����������������ڷ���ֵ
    reference operator*() {
        return isObject_ ? objectIterator_->second : *arrayIterator_;
    }

    // ��Ա���������
    pointer operator->() {
        return &(operator*());
    }

    // ǰ�õ��������
    ValueIterator& operator++() {
        if (isObject_) {
            ++objectIterator_;
        }
        else {
            ++arrayIterator_;
        }
        return *this;
    }

    // ���õ��������
    ValueIterator operator++(int) {
        ValueIterator temp = *this;
        ++(*this);
        return temp;
    }

    // ǰ�õݼ������
    ValueIterator& operator--() {
        if (isObject_) {
            --objectIterator_;
        }
        else {
            --arrayIterator_;
        }
        return *this;
    }

    // ���õݼ������
    ValueIterator operator--(int) {
        ValueIterator temp = *this;
        --(*this);
        return temp;
    }

    // ��������
    bool operator==(const ValueIterator& other) const {
        return isObject_ ? objectIterator_ == other.objectIterator_
            : arrayIterator_ == other.arrayIterator_;
    }

    // ����������
    bool operator!=(const ValueIterator& other) const {
        return !(*this == other);
    }

private:
    typename Value::Array::iterator arrayIterator_;
    typename Value::Object::iterator objectIterator_;
    bool isObject_ = false; // ��ʶ��ǰ�������Ƿ����ڶ���
};

// ���峣��������
template<typename ValueType>
class ConstValueIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = const ValueType*;
    using reference = const ValueType&;

    // Ĭ�Ϲ��캯��
    ConstValueIterator() = default;

    // ���캯�������������͵ĳ���������
    ConstValueIterator(typename Value::Array::const_iterator arrayIt)
        : arrayIterator_(arrayIt), isObject_(false) {}

    // ���캯�����ڶ������͵ĳ���������
    ConstValueIterator(typename Value::Object::const_iterator objectIt)
        : objectIterator_(objectIt), isObject_(true) {}

    // ����������������ڷ���ֵ
    reference operator*() const {
        return isObject_ ? objectIterator_->second : *arrayIterator_;
    }

    // ��Ա���������
    pointer operator->() const {
        return &(operator*());
    }

    // ǰ�õ��������
    ConstValueIterator& operator++() {
        if (isObject_) {
            ++objectIterator_;
        }
        else {
            ++arrayIterator_;
        }
        return *this;
    }

    // ���õ��������
    ConstValueIterator operator++(int) {
        ConstValueIterator temp = *this;
        ++(*this);
        return temp;
    }

    // ǰ�õݼ������
    ConstValueIterator& operator--() {
        if (isObject_) {
            --objectIterator_;
        }
        else {
            --arrayIterator_;
        }
        return *this;
    }

    // ���õݼ������
    ConstValueIterator operator--(int) {
        ConstValueIterator temp = *this;
        --(*this);
        return temp;
    }

    // ��������
    bool operator==(const ConstValueIterator& other) const {
        return isObject_ ? objectIterator_ == other.objectIterator_
            : arrayIterator_ == other.arrayIterator_;
    }

    // ����������
    bool operator!=(const ConstValueIterator& other) const {
        return !(*this == other);
    }

private:
    typename Value::Array::const_iterator arrayIterator_;
    typename Value::Object::const_iterator objectIterator_;
    bool isObject_ = false; // ��ʶ��ǰ�������Ƿ����ڶ���
};


}
#endif // JSON_VALUEITERATOR_HPP
