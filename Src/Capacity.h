#pragma once

class Capacity {
public:
	Capacity() = default;
	virtual ~Capacity() = default;

	virtual size_t size() const final {
		return _count;
	}

	virtual size_t length() const final {
		return _count;
	}

	virtual size_t count() const final {
		return _count;
	}

	virtual bool empty() const final {
		return _count == 0;
	}

	virtual void clear() = 0;
protected:
	size_t _count = 0;
};

