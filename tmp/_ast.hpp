class Expression {
public:
    virtual ~Expression () {}

    virtual Expression * clone () = 0;

    virtual int value () = 0;
};

class Plus: public Expression {
    Expression * m_left;
    Expression * m_right;

public:
    Plus (
        Expression * left,
        Expression * right):
        m_left  {left},
        m_right {right} {}

    Plus (Plus const & other) {
        m_left  = other.m_left ->clone ();
        m_right = other.m_right->clone ();
    }

    ~Plus () override {
        delete m_left;
        delete m_right;
    }

    Plus & operator = (Plus const & other) {
        if (&other != this) {
            delete m_left;
            delete m_right;

            m_left  = other.m_left ->clone ();
            m_right = other.m_right->clone ();
        }
        return *this;
    }

    Expression * clone () override { return new Plus{*this}; }

    int value () override { return m_left->value () + m_right->value (); }

};

class Times: public Expression {
    Expression * m_left;
    Expression * m_right;

public:
    Times (
        Expression * left,
        Expression * right):
        m_left  {left},
        m_right {right} {}

    Times (Times const & other) {
        m_left  = other.m_left ->clone ();
        m_right = other.m_right->clone ();
    }

    ~Times () override {
        delete m_left;
        delete m_right;
    }

    Times & operator = (Times const & other) {
        if (&other != this) {
            delete m_left;
            delete m_right;

            m_left  = other.m_left ->clone ();
            m_right = other.m_right->clone ();
        }
        return *this;
    }


    Expression * clone () override { return new Times{*this}; }

    int value () override { return m_left->value () * m_right->value (); }

};

// For numbers
class Number: public Expression {
    int m_val;

public:
    Number (int val): m_val {val} {}

    Number (Number const & other) { m_val = other.m_val; }

    Number &operator = (Number const & other) {
        if (&other != this)
            m_val = other.m_val;
        return *this;
    }

    Expression * clone () override { return new Number{*this}; }

    int value () override { return m_val; }
};

// For identifiers
class Ident: public Expression {
    int * m_val;

public:
    Ident (int * val): m_val {val} {}

    // Copy constructor
    Ident (const Ident &other) { m_val = other.m_val; }

    Ident &operator = (const Ident &other) {
        if (&other != this)
            m_val = other.m_val;
        return *this;
    }

    Expression * clone () override { return new Ident{*this}; }


    int value () override { return *m_val; }
};
