#include "Vector.h"



/************************************************************************/
/* CONSTRUCTORS                                                         */
/************************************************************************/

template<typename T>
Vector<T>::Vector(Vector<T>::ctor ) :
	BasicVector<T>(BasicVector<T>::ctor::null)
{}


template<typename T>
Vector<T>::Vector( void ) :
	BasicVector<T>(),
	maxSize( 0 ),
	iteratorEnd( NULL ) {

}



template<typename T>
template<typename C>
Vector<T>::Vector( const Vector<C> & vector ) :
	BasicVector<T>(BasicVector<T>::ctor::null),
	maxSize( vector.getMaxSize() ),
{
	this->size = vector.getSize();
	this->dataTable = ( this -> maxSize ) ? new T[ this -> maxSize ] : NULL;
	copy( this -> dataTable, vector.getData(), this -> maxSize );
	_updateIterators();
}



template<typename T>
Vector<T>::Vector( Vector && v ) :
	BasicVector<T>(Utility::toRValue(v)),
	maxSize( Utility::toRValue( v.maxSize ) ) {
	_updateIterators();
}






template<typename T>
Vector<T>::Vector( const Size size, const Size maxSize ) :
	BasicVector<T>(BasicVector<T>::ctor::null),
	maxSize( maxSize ),
	iteratorEnd( dataTable + maxSize )
{
	_assert(maxSize);
	this->size = size;
	this->dataTable = new T[ maxSize ];
	_updateIterators();
}

template<typename T>
Vector<T>::Vector( const Size maxSize ) :
	Vector<T>( maxSize, maxSize ) {}


template<typename T>
template<typename C>
inline Vector<T>::Vector(const BasicVector<C>& vector) :
	BasicVector<T>(vector),
	maxSize(vector.getSize())
{
	_updateIterators();
}

template<typename T>
template<typename C, size_t N>
Vector<T>::Vector( const C( &data )[ N ] ) :
	Vector<T>( data, N ) {}

/*
template<typename T>
Vector<T>::Vector(const T * data, Size maxSize) :
maxSize(maxSize),
size(maxSize),
dataTable(new T[size])
{
	copy(data, this -> size);
	_updateIterators();
}

template<typename T>
Vector<T>::Vector(const T * data, Size size, Size maxSize) :
	maxSize(maxSize),
	size(size),
	dataTable(new T[maxSize])
{
	copy(data, this -> size);
	_updateIterators();
}
*/


template<typename T>
template<typename C>
Vector<T>::Vector( const C * data, const Size size ) :
	Vector<T>( data, size, size ) {}


template<typename T>
template<typename C>
Vector<T>::Vector( const C * data, const Size size, const Size maxSize ) :
	BasicVector<T>(BasicVector<T>::ctor::null),
	maxSize( maxSize )
{
	_assert( maxSize );
	_assert( maxSize >= size );

	this->size = size;
	this->dataTable = new T[ maxSize ];
	copy( data, this -> size );
	_updateIterators();
}

template<typename T>
template<typename C>
Vector<T>::Vector( const typename RandomAccessIterator<C> beginIt, const typename RandomAccessIterator<C> endIt ) :
	Vector<T>( beginIt, static_cast< Size >( endIt - beginIt ) ) {}


template<typename T>
Vector<T>::~Vector( void ) {
	
}















template<typename T>
template<typename C>
void Vector<T>::copy( Vector<C> vector, Size indexSrc, const Size indexDst, Size size ) {
	allocate( size + indexDst );
	Utility::copy( this -> dataTable + indexDst, vector.getData() + indexSrc, size );
}



template<typename T>
template<typename C>
void Vector<T>::copy( const C * datas, const Size index, const Size size ) {
	Utility::copy( this -> dataTable + index, datas, size );
}

template<typename T>
template<typename C>
void Vector<T>::copy( const C * datas, const Size size ) {
	Utility::copy( this -> dataTable, datas, size );
}

template<typename T>
template<typename C>
Vector<T> & Vector<T>::operator+=( const Vector<C> & vector ) {
	concat( vector );
	return *this;
}

template<typename T>
template<typename C>
void Vector<T>::concat( const Vector<C> & vector ) {
	if ( vector.size > Size(0) ) {
		const Size oldSize(this->size);
		this -> resize(this -> size + vector.size);
		Utility::copy(this->dataTable + oldSize, vector.dataTable, vector.size);
	}
}

template<typename T>
template<typename C>
void Vector<T>::createFromData( const C * dataTable, const Size size ) {
	delete[] this -> dataTable;
	this -> dataTable = new T[ size ];

	Utility::copy( this -> dataTable, dataTable, size );


	this -> size = size;
	this -> maxSize = size;
	_updateIterators();
}


template<typename T>
void Vector<T>::reset() {
	resize( 0 );
}


/************************************************************************/
/* LOGICAL                                                              */
/************************************************************************/



template<typename T>
bool Vector<T>::operator==( const T & v ) const {
	if ( this -> size != 1 )
		return false;

	return this -> dataTable[ 0 ] == v;
}

template<typename T>
bool Vector<T>::operator!=( const T & v ) const {
	if ( this -> size != 1 )
		return true;
	return this -> dataTable[ 0 ] != v;
}
template<typename T>
bool Vector<T>::operator<( const T & v ) const {
	if ( this -> size < 1 )
		return true;
	return this -> dataTable[ 0 ] < v;
}
template<typename T>
bool Vector<T>::operator>( const T & v ) const {
	if ( this -> size < 1 )
		return false;
	return this -> dataTable[ 0 ] > v;
}
template<typename T>
bool Vector<T>::operator<=( const T & v ) const {
	if ( this -> size < 1 )
		return true;
	else if ( this -> size == 1 )
		return this -> dataTable[ 0 ] <= v;
	return false;
}
template<typename T>
bool Vector<T>::operator>=( const T & v ) const {
	if ( this -> size < 1 )
		return false;
	else if ( this -> size == 1 )
		return this -> dataTable[ 0 ] >= v;
	else
		return this -> dataTable[ 0 ] == v;
}


template<typename T>
bool Vector<T>::eraseAll( const T & value ) {
	bool r( false );
	for ( Size i( 0 ); i < this -> maxSize; i++ ) {
		if ( value == this -> dataTable[ i ] ) {
			eraseI( i );
			r = true;
		}
	}
	return r;
}

template<typename T>
void Vector<T>::resize( const Size newSize ) {
	if ( newSize > this -> maxSize )
		reserve( newSize );

	this -> size = newSize;
	_updateIterators();
}

template<typename T>
inline void Vector<T>::resizeNoCopy(const Size newSize) {
	if ( newSize > this -> maxSize )
		allocate(newSize);

	this -> size = newSize;
	_updateIterators();
}

template<typename T>
void Vector<T>::extendLeft( const Size increasedSize ) {
	// Resize !
	resize( this -> size + increasedSize );

	// Shift Right
	Size iSrc( this -> size - increasedSize - 1 );
	Size iDst( this -> size - 1 );
	for ( ; iDst >= increasedSize; iSrc--, iDst-- ) {
		this->dataTable[ iDst ] = this->dataTable[ iSrc ];
	}
}

template<typename T>
void Vector<T>::extendRight( const Size increasedSize ) {
	resize( this -> size + increasedSize );
}



template<typename T>
bool Vector<T>::eraseFirst( const T & v ) {
	for ( Size i( 0 ); i < this -> size; i++ ) {
		if ( v == this -> dataTable[ i ] ) {
			eraseI( i );
			return true;
		}
	}
	return false;
}

template<typename T>
void Vector<T>::eraseI( const Size index ) {
	for ( Size i( index ); i < this -> size - 1; i++ ) {
		this -> dataTable[ i ] = this -> dataTable[ i + 1 ];
	}
	this -> size--;
	_updateIterators();
}

template<typename T>
void Vector<T>::eraseIt( const typename Vector<T>::Iterator it ) {
	typename Vector<T>::Iterator itSrc( it + 1 );
	typename Vector<T>::Iterator itDst( it );

	for ( ; itSrc < getEnd(); iterate( &itSrc ), iterate( &itDst ) ) {
		setValueIt( itDst, getValueIt( itSrc ) );
	}
	this -> size--;
	_updateIterators();
}

template<typename T>
T & Vector<T>::pop() {
	this -> size--;
	_updateIterators();
	return *this -> iteratorEnd;
}





template<typename T>
void Vector<T>::setValueI(const Size i, const T& data) {
#ifdef DEBUG
	if ( i >= this->maxSize ) {
		_error("Vector::setValueI Out of bounds.");
	}
#endif
	this -> dataTable[ i ] = data;
}

template<typename T>
void Vector<T>::setValueIt(typename Vector<T>::Iterator i, const T& data) {
#ifdef DEBUG
	if ( i < this->dataTable || i >= this->iteratorEnd ) {
		_error("Vector::setValueIt Out of bounds.");
	}
#endif
	* i = data;
}

template<typename T>
const T& Vector<T>::getValueI(const Size i) const {
	return const_cast< Vector<T> * >( this )->getValueI(i);
}

template<typename T>
T& Vector<T>::getValueI(const Size i) {
#ifdef DEBUG
	if ( i >= this->maxSize ) {
		_error("Vector::getValueI Out of bounds.");
	}
#endif
	return this -> dataTable[ i ];
}

template<typename T>
const T& Vector<T>::getValueIt(typename Vector<T>::Iterator it) const {
	return const_cast< Vector<T> * >( this )->getValueIt(it);
}

template<typename T>
T& Vector<T>::getValueIt(typename Vector<T>::Iterator it) {
#ifdef DEBUG
	if ( it < this->dataTable || it >= this->iteratorEnd ) {
		_error("Vector::getValueIt Out of bounds.");
	}
#endif
	return *it;
}







/************************************************************************/
/* OPERATOR =                                                           */
/************************************************************************/
template<typename T>
Vector<T> & Vector<T>::operator=( Vector<T> && v ) {
	BasicVector<T>::operator=(Utility::toRValue(v));

	this -> maxSize = Utility::toRValue( v.maxSize );
	_updateIterators();

	return *this;
}

template<typename T>
template<typename C>
Vector<T> & Vector<T>::operator=( const Vector<C> & vector ) {
	this -> maxSize = vector.getMaxSize();
	this -> size = vector.getSize();

	if ( this->dataTable ) {
		delete[] this -> dataTable;
	}
	this -> dataTable = ( this -> maxSize ) ? new T[ this -> maxSize ] : NULL;
	copy( this -> dataTable, vector.dataTable, this -> size );
	_updateIterators();

	return *this;
}

template<typename T>
template<typename C>
inline Vector<T>& Vector<T>::operator=(const BasicVector<C>& vector) {
	BasicVector<T>::operator=(vector);

	this->maxSize = this->size;
	_updateIterators();

	return *this;
}

template<typename T>
bool Vector<T>::isEmpty() const {
	return ( this -> size == 0 );
}

template<typename T>
void Vector<T>::clear() {
	this -> size = 0;
	_updateIterators();
}

template<typename T>
const Size Vector<T>::getMaxSize() const {
	return this -> maxSize;
}


template<typename T>
void Vector<T>::reserve( const Size newMax ) {
	if ( this -> size > newMax )
		this -> size = newMax;

	if ( newMax == Size(0) ) {
		delete[] this -> dataTable;
		this -> dataTable = NULL;
	} else {
		T * newTable = new T[ newMax ];

		if ( this->maxSize > Size(0) ) {
			// Copy old data
			Utility::copy(newTable, dataTable, this -> size);

			delete[] this -> dataTable;
		}
		this -> dataTable = newTable;
	}
	this -> maxSize = newMax;
	_updateIterators();
}

template<typename T>
T * Vector<T>::push( const T & data ) {
	if ( this -> maxSize == this -> size ) {
		Size newSize( this -> size + 1 );
		_extendBuffer( newSize );
		T * valueP( this -> dataTable + ( this -> size ) );
		( *valueP ) = data;
		this -> size = newSize;
		_updateIterators();
		return valueP;
	} else {
		T * valueP( this -> dataTable + ( this -> size ) );
		( *valueP ) = data;
		this -> size++;
		_updateIterators();
		return valueP;
	}
}

template<typename T>
void Vector<T>::inserti( const Size i, const T & v ) {
	if ( this -> maxSize == this -> size ) {
		Size newSize( this -> size + 1 );
		_extendBuffer( newSize );
		this -> size = newSize;
		_updateIterators();
	} else {
		this -> size++;
		_updateIterators();
	}
	for ( Size k = this -> size - 1, j = this -> size - 2; k > i; k--, j-- )
		setValueI( k, getValueI( j ) );
	this -> dataTable[ i ] = v;
}


template<typename T>
void Vector<T>::_extendBuffer( const Size newSizeNeeded ) {
	this -> maxSize = newSizeNeeded * 2;
	T * newBuffer = new T[ this -> maxSize ];
	if ( this -> dataTable != NULL ) {
		copy( newBuffer, this -> dataTable, this -> size );
		delete[] this -> dataTable;
	}
	this -> dataTable = newBuffer;
}


template<typename T>
void Vector<T>::allocate( const Size newMax ) {
	delete[] this -> dataTable;
	if ( newMax )
		this -> dataTable = new T[ newMax ];
	else
		this -> dataTable = NULL;

	this -> maxSize = newMax;
	_updateIterators();
}


template<typename T>
void Vector<T>::_allocateNoNullDelete( const Size newMax ) {
	this -> dataTable = new T[ newMax ];
	this -> maxSize = newMax;
}


template<typename T>
void Vector<T>::_allocateNoNull( const Size newMax ) {
	delete[] this -> dataTable;
	this -> dataTable = new T[ newMax ];
	this -> maxSize = newMax;
}





template<typename T>
std::ostream & operator<<( std::ostream & stream, const Vector<T> & vector ) {
	stream << "[ ";
	for ( Size i( 0 ); i < vector.getSize(); i++ ) {
		if ( i ) stream << " | ";
		stream << vector[ i ];
	}
	stream << " ];";
	return stream;
}







template<typename T>
void Vector<T>::_updateIterators() {
	this -> iteratorEnd = this -> dataTable + this -> size;
}

/*
template<typename T>
T & Vector<T>::operator[]( typename Vector<T>::RandomAccessIterator i ){
	return *i;
}

template<typename T>
const T & Vector<T>::operator[]( typename Vector<T>::RandomAccessIterator i ) const{
	return *i;
}
*/


template<typename T>
void Vector<T>::_erasei( const Size i ) {
	_eraseit( getData() + i );
}


template<typename T>
void Vector<T>::_eraseit( typename Vector<T>::Iterator it ) {
#ifdef DEBUG
	if ( it < this->dataTable || it >= this->iteratorEnd ) {
		_error("Vector::_eraseit Out of bounds.");
	}
#endif
	this -> size--;
	_updateIterators();
	for ( typename Vector<T>::Iterator it( it ); it != getEnd(); iterate( &it ) ) {
		*it = *( it + 1 );
	}
}


















template<typename T>
template<typename Stream>
bool Vector<T>::read( Stream * stream ) {

	if ( !IO::read( stream, &this -> size ) ) {
		_clear();
		return false;
	}
	allocate( this -> size );

	for ( Size i( 0 ); i < this -> size; i++ ) {
		if ( !IO::read( stream, &( this -> dataTable[ i ] ) ) ) {
			_clear();
			return false;
		}
	}

	return true;
}

template<typename T>
void Vector<T>::_clear() {
	this -> size = 0;
	this -> maxSize = 0;
	delete[] this -> dataTable;
	this -> dataTable = NULL;
	_updateIterators();
}
