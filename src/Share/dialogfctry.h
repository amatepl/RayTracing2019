#ifndef DIALOGFCTRY_H
#define DIALOGFCTRY_H

#include <memory>

using namespace std;

/*!
 * \class DialogWinFctry
 */
template <class DialogWin>
class DialogWinFctry{
public:
    ~DialogWinFctry(){}
    virtual unique_ptr<DialogWin> create() = 0;
};

/*!
 * \class DerivedDialogWinFctry
 *
 */
template <class Derived, class Base, class MathItem>
class DerivedDialogWinFctry: public DialogWinFctry<Base>
{
    MathItem *m_mathItem;
public:
    DerivedDialogWinFctry(MathItem *mathItem): m_mathItem{mathItem}{}
    unique_ptr<Base> create(){
        return unique_ptr<Base>(new Derived(m_mathItem));
    }
};

#endif // DIALOGFCTRY_H
