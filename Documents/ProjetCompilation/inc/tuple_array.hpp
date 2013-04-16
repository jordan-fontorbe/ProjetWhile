/*
*	Membres du groupes
*	Kong Win Chang Bryan		10907494
*	Lecomte Antoine			11209095
*	Minot Maël			10908192
*	Roullet Pierre-Allain		10907316
*/
#ifndef TUPLE_ARRAY_HPP
#   define TUPLE_ARRAY_HPP

class TupleArray
{
    protected:
    	bool estId;
    	int val;

    public:
        TupleArray(bool etreId, int avoirVal);
        bool getEstId() { return estId; }
        int getVal() { return val; }
};

#endif /* TUPLE_ARRAY */
