/*
 * CBtreeFunc.cpp
 *
 *  Created on: 2012-3-5
 *      Author: liyouhuan
 */
#include "CBtreeH.h"
using namespace std;
KeyType KeyNULL;

eletype _eletype;
int _ii;
string filePath_s2sID;
string filePath_sID2s;
string filePath_o2sID;
string filePath_opID2sID;
FILE * _log_btree;
// ���м����в����
bool mItnlNode::Insert( mNode * pNode)
{
	if(getCount() >= MAXNUM_KEY)
	{
		printf("err large\n");
		return false;
	}
	KeyType & data = pNode ->getKey(1);
//	for check

	int _ikey = this ->iInsert(data);
	if(_ikey <= 1)
	{
		printf("err in insert itnl\n");
		system("pause"); exit(0);
	}
//	��Ҫ����ĵ��������Ҷ�ʱҪ���⴦��, solved
	for(int i = getCount() + 1; i > _ikey; i --)
	{
		this ->setElement(i,  this ->getElement(i - 1) );
	}
	mitnldata _mitnl;
	_mitnl.mitnldata_Initial();
	_mitnl.mPointer = pNode;
	_mitnl.mAddr_sonFB = pNode ->getAddrFB();
	_mitnl.mKey = data;
	this ->setElement(_ikey, _mitnl);
	this ->IncCount();
	pNode ->setFather(this);
	this ->setMemory(_ikey);
	this ->setModify();
	return true;
}

// ���м�����ɾ�������Լ��ü����ָ��
int mItnlNode::Delete(const KeyType & _keytype)
{
	int _index = -1;
	int _ibegin = 1, _iend = getCount();
	int _imiddle;
	// ���ֲ���index
	while(_ibegin < _iend)
	{
		_imiddle = (_ibegin + _iend) / 2;
		if(ItnlData[_ibegin].mKey == _keytype)
		{
			_index =  _ibegin;
			break;
		}
		if(ItnlData[_iend].mKey == _keytype)
		{
			_index =  _iend;
			break;
		}
		if(_ibegin == _iend - 1)	break;
		if(ItnlData[_imiddle].mKey> _keytype)
		{
			_iend = _imiddle;
		}
		else
		{
			_ibegin = _imiddle;
		}
	}

	//�κ�һ�����Ǹ��ڵ����Ҷ�ӽڵ�Ľڵ���뱣֤������������Ԫ��
	// ����insert�� index = 1 ��ʱ��һ���������������ұߣ�����
	// delete��ͬ
	if(_index == 1 && this ->getFather() != NULL)
	{
		mItnlNode * itnl_father = (mItnlNode *)(this ->getFather() );
		KeyType & f_data = this ->getKey(1);
		KeyType & i_data = this ->getKey(2);
		while(itnl_father != NULL)
		{
			// �˴�ͬinsert��ͬ�������䲻֮ͬ��
			int tmp_key = itnl_father ->iExist(f_data);
			if(tmp_key < 1)
			{
				cout << "bug tmp_key" << endl;
				system("pause");
				exit(0);
			}
			itnl_father ->setKey(tmp_key, i_data);
			itnl_father ->setMemory(tmp_key);
			itnl_father ->setModify();
			if(tmp_key != 1) break;

			itnl_father = (mItnlNode *)(itnl_father ->getFather()  );
		}
	}
	if(_index > 0 && _index <= getCount())
	{
		for(int i = _index; i < getCount(); i ++)
		{
			this ->setElement(i, this ->getElement(i + 1)  );
		}
		(this ->getElement(getCount()) ).cleardata();
		this ->DecCount();
		this ->setModify();
		return _index;
	}
	else
	{
		cout << "bug index" << endl;
	}
	return -1;
}
KeyType & mItnlNode::Split(mItnlNode* pNode)
{
	pNode ->setCount(ORDER_V);
	for(int i = ORDER_V + 1; i <= MAXNUM_KEY; i ++)
	{
		pNode ->setElement(i - ORDER_V,   this ->getElement(i)  );

		if(pNode ->isInMemory(i - ORDER_V))//debug for long time!!!
		{
			(   pNode ->getPointer(i - ORDER_V)   ) ->setFather(pNode);
		}
	}
	this ->setCount(ORDER_V);
	this ->setModify();
	pNode ->setModify();
	return (pNode ->getElement(1)).mKey;
}

// ��Ͻ�㣬��ָ���м��������ȫ�����е����м���
bool mItnlNode::Combine(mItnlNode * pNode)
{
	if(this ->getCount() + pNode ->getCount() > MAXNUM_KEY)
		return false;
	int _count = this ->getCount();
	for(int i = 1; i <= pNode ->getCount(); i ++)
	{
		this ->setElement(_count + i, pNode ->getElement(i) );
		this ->IncCount();
	}
	return true;
}

// ����һ�����һ��Ԫ�ص������
bool mItnlNode::MoveOneElement(mNode* pNode)
{


	return false;
}

// ���Ҷ�ӽ���е�����

// ��Ҷ�ӽ���в�������
bool mLeafNode::Insert(const mleafdata & _leafdata)
{
	const KeyType & data = _leafdata.mData;
	{
//		fputs(data.sKey, _log_btree);
//		fputs("\n", _log_btree);
	}
	if(getCount() >= MAXNUM_KEY)
	{
		printf("err count too large\n");
		return false;
	}
//	����i�� data ����i - 1 �� i ֮��, Ҫ����i ��
	int _i_insert = this ->iInsert(data);
//	��Ҫ���ǽ����ڵ���Ҷ�ӽڵ������� ��Ҫ�ټӸ�����
	if(_i_insert == 1 && this ->getFather() != NULL)
	{
		mItnlNode * _pFather = (mItnlNode *)(this ->getFather());
		KeyType & f_data	= this ->getKey(1);
		while(_pFather != NULL)
		{
			int _ikey = _pFather ->iExist(f_data);
			//check
			if(_ikey <= 0 || _ikey > _pFather ->getCount())
			{
				printf("err in _ikey\n");
				system("pause");
				exit(0);
			}
			//ͬ��ʹ���ڴ�λ������λʧЧ�� ����ʧ�ߣ� �ֲ�֮����
			_pFather ->setKey(_ikey, _leafdata.mData);
			_pFather ->setMemory(_ikey);
			_pFather ->setModify();
			_pFather = (mItnlNode *)(_pFather ->getFather());
		}
	}

	for(int i = getCount() + 1; i > _i_insert; i --)
	{
		this ->setElement(i,  this ->getElement(i - 1)  );
	}

	this ->setElement(_i_insert, _leafdata);
	this ->IncCount();
	this ->setModify();
	return true;
}

/*
 * ɾ���ɹ�����ɾ����key���±꣬ ʧ���򷵻�-1
 * �����޸�λ
 * ��������˵�Ԫ���������޸Ķ�Ӧ��Ҫ�޸ĵĸ��ڵ㣬 �˴���insert��ͬ
 * insert����������˱�Ȼ���������������
 */
int mLeafNode::Delete(KeyType & _keytype)
{
	int _index = -1;
	int _ibegin = 1, _iend = getCount();
	int _imiddle;
	while(_ibegin < _iend)
	{
		_imiddle = (_ibegin + _iend) / 2;
		if(LeafData[_ibegin].mData == _keytype)
		{
			_index =  _ibegin;
			break;
		}
		if(LeafData[_iend].mData == _keytype)
		{
			_index =  _iend;
			break;
		}
		if(_ibegin == _iend - 1)	break;
		if(LeafData[_imiddle].mData> _keytype)
		{
			_iend = _imiddle;
		}
		else
		{
			_ibegin = _imiddle;
		}
	}
	//�κ�һ�����Ǹ��ڵ����Ҷ�ӽڵ�Ľڵ���뱣֤������������Ԫ��
	// ����insert�� index = 1 ��ʱ��һ���������������ұߣ�����
	// delete��ͬ
	if(_index == 1 && this ->getFather() != NULL)
	{
		mItnlNode * itnl_father = (mItnlNode *)(this ->getFather() );
		KeyType & f_data = this ->getKey(1);
		KeyType & i_data = this ->getKey(2);
		while(itnl_father != NULL)
		{
			// �˴�ͬinsert��ͬ�������䲻֮ͬ��
			int tmp_key = itnl_father ->iExist(f_data);
			if(tmp_key < 1)
			{
				cout << "bug tmp_key" << endl;
				system("pause"); exit(0);
			}
			itnl_father ->setKey(tmp_key, i_data);
			itnl_father ->setMemory(tmp_key);
			itnl_father ->setModify();
			if(tmp_key != 1) break;

			itnl_father = (mItnlNode *)(itnl_father ->getFather()  );
		}
	}
	if(_index > 0 && _index <= getCount())
	{
		(this ->getElement(_index)).cleardata();
		for(int i = _index; i < getCount(); i ++)
		{
			this ->setElement(i, this ->getElement(i + 1)  );
		}
		(this ->getElement(getCount() )).cleardata();
		this ->DecCount();
		this ->setModify();
		return _index;
	}
	else
	{
		cout << "bug index" << endl;
	}
	return -1;
}
//����delete of leaf
int mLeafNode::Delete(KeyType & _keytype, char partval[], int & pvFlag)
{
	int _index = -1;
	int _ibegin = 1, _iend = getCount();
	int _imiddle;
	while(_ibegin < _iend)
	{
		_imiddle = (_ibegin + _iend) / 2;
		if(LeafData[_ibegin].mData == _keytype)
		{
			_index =  _ibegin;
			break;
		}
		if(LeafData[_iend].mData == _keytype)
		{
			_index =  _iend;
			break;
		}
		if(_ibegin == _iend - 1)	break;

		if(LeafData[_imiddle].mData> _keytype)
		{
			_iend = _imiddle;
		}
		else
		{
			_ibegin = _imiddle;
		}
	}

	if(_index <= 0 || _index > getCount())	return -1;
	bool del_pv_ret = this ->getElement(_index).deletePartVal(partval, pvFlag);

	// delete fail, return false;
	if(del_pv_ret ==  false)
		return -1;

	// delete successfully and element no null, return true
	if(pvFlag == FLAG_NO_ZERO)
		return _index;

	//���ɾ���ɹ�����Ԫ�ر�Ϊ�գ� �����ɾ����Ӧ��key


	//�κ�һ�����Ǹ��ڵ����Ҷ�ӽڵ�Ľڵ���뱣֤������������Ԫ��
	// ����insert�� index = 1 ��ʱ��һ���������������ұߣ�����
	// delete��ͬ
	if(_index == 1 && this ->getFather() != NULL)
	{
		mItnlNode * itnl_father = (mItnlNode *)(this ->getFather() );
		KeyType & f_data = this ->getKey(1);
		KeyType & i_data = this ->getKey(2);
		while(itnl_father != NULL)
		{
			// �˴�ͬinsert��ͬ�������䲻֮ͬ��
			int tmp_key = itnl_father ->iExist(f_data);
			if(tmp_key < 1)
			{
				cout << "bug tmp_key" << endl;
				system("pause"); exit(0);
			}
			itnl_father ->setKey(tmp_key, i_data);
			itnl_father ->setMemory(tmp_key);
			itnl_father ->setModify();
			if(tmp_key != 1) break;

			itnl_father = (mItnlNode *)(itnl_father ->getFather()  );
		}
	}
	if(_index > 0 && _index <= getCount())
	{
		(this ->getElement(_index)).cleardata();
		for(int i = _index; i < getCount(); i ++)
		{
			this ->setElement(i, this ->getElement(i + 1)  );
		}
		(this ->getElement(getCount() )).cleardata();
		this ->DecCount();
		this ->setModify();
		return _index;
	}
	return -1;
}



// ����Ҷ�ӽ�㣬�ѱ�Ҷ�ӽ��ĺ�һ�����ݼ��е�ָ����Ҷ�ӽ����
KeyType & mLeafNode::Split(mLeafNode * pNode)
{
	for(int i = ORDER_V + 1; i <= MAXNUM_KEY; i ++)
	{
		pNode ->setElement(i - ORDER_V,   this ->getElement(i)  );
	}
	this ->setCount(ORDER_V);
	pNode ->setCount(ORDER_V);
	this ->setModify();
	pNode ->setModify();
	return (pNode ->getElement(1)).mData;
}

// ��Ͻ�㣬��ָ��Ҷ�ӽ�������ȫ�����е���Ҷ�ӽ��
bool mLeafNode::Combine(mLeafNode * pNode)
{
	int this_count = this ->getCount();
	int pnode_count = pNode ->getCount();
	for(int i = 1; i <= pnode_count; i ++)
	{
		this ->setElement(this_count + i, pNode ->getElement(i) );
		this ->IncCount();
	}
	return false;
}
// ���Ҷ�Ӧ��Ҷ�ӽ��
mLeafNode* BPlusTree::SearchLeafNode(const KeyType & data)const
{
	mNode * pNode = mRoot;
	if(mRoot ->getType() == NODE_TYPE_LEAF)
	{
		return (mLeafNode *)mRoot;
	}
	else// no check
	{
		/*
		 * while ѭ��
		 * ��ǰ�����м�ڵ�
		 * �ҵ��²�����±�
		 * �ж��Ƿ񳬳���߽磬 �ǵĻ�ֱ�ӵ��ף� pNode ָ��Ҷ�ӽڵ㣬 break
		 * ��֮�� ���϶���pNodeָ��Ҷ�ӽڵ�
		 * ���ԣ� ����ʱ��Ҫ�ж��Ƿ񳬹���߽磬 �ǵĻ�Ҫ�޸��ϲ㸸�ڵ����߽�
		 * Search ��ʱ��Ҫע��߽�������ж�, ���е�ǰҶ�ڵ�����Ǹ��ڵ�
		 */
//	    int _floor = 1;
		while(pNode ->getType() == NODE_TYPE_INTERNAL)
		{
			mItnlNode * _pItnl = (mItnlNode *)pNode;
			int _enter_ret = _pItnl ->iNextFloor(data);
			int _enter_num = _enter_ret;
			if(_enter_ret <= 0)
			{
				_enter_num = 1;
			}
			bool _in_memory = _pItnl ->isInMemory(_enter_num);
			if(!_in_memory)
			{
				long long int _addrfb = _pItnl ->getSonAddr(_enter_num);
				mNode * _pmnode = ReadNode(mfp, _addrfb);
				_pItnl ->setPointer(_enter_num, _pmnode);
				_pItnl ->setMemory(_enter_num);
				pNode = _pmnode;
			}
			else
			{
				pNode = pNode ->getPointer(_enter_num);
			}
		}
		if(pNode == NULL){
			cout << "pNode is err in searchLeafNode" << endl;
			system("pause"); exit(0);
		}
		if(pNode ->getType() != NODE_TYPE_LEAF)
		{
			cout << "err in searchleafnode" << endl;
			system("pause"); exit(0);
		}
		return (mLeafNode*) pNode;
	}
	return NULL;
}
// �����в�������
bool BPlusTree::Search(KeyType & data, mleafdata & _ret)//����һ������ ���ڽ��ղ��ҹ����н����Ҷ�ӽڵ�
{
	mLeafNode * _pLeaf = SearchLeafNode(data);
	int _ikey = _pLeaf ->iExist(data);
	if(_ikey > _pLeaf ->getCount())
	{
		printf("err in ikey\n");
		exit(0);
	}
	if(_ikey > 0)
	{
		/* mValue* in _ret should not be released */
		_ret.assign_val_ptr(_pLeaf ->getElement(_ikey));
//		_ret = _pLeaf ->getElement(_ikey);
		return true;
	}

	//cout << "not find, the iKey is " << _ikey << endl;
	return false;
}

bool BPlusTree::Insert(const mleafdata & _leafdata)
{
	{

	}
	const KeyType & data = _leafdata.mData;
	mLeafNode * _pOldLeaf = SearchLeafNode(data);
	int _ikey = _pOldLeaf ->iExist(data);
	if(_ikey > 0)
	{
		_pOldLeaf ->dupInsert(_leafdata, _ikey);
		return false;
	}
	{
		this ->insert_count ++;
	}
	if(_pOldLeaf ->getCount() < MAXNUM_KEY)
	{
		if(! _pOldLeaf ->getModify())
		{
			DelDisk(mfp, _pOldLeaf ->getAddrFB(), mblockQueue);
		}
//		setmodified in insert
		return _pOldLeaf ->Insert(_leafdata);
	}
	else
	{
//		set modified in mnode_initial;
		mLeafNode * _pNewLeaf = new mLeafNode;
//		new node need a addrfb
		long long int _addr_newleaf = mblockQueue.Pop();
		_pNewLeaf ->setAddrFB(_addr_newleaf);

//		_key_tmp Ҳ�ͽ���_pnewleaf�ĵ�һ��Ԫ�ص�key
//		setmodified in split;
		if(! _pOldLeaf ->getModify())
		{
			DelDisk(mfp, _pOldLeaf ->getAddrFB(), mblockQueue);
		}
		KeyType &_key_tmp = _pOldLeaf ->Split(_pNewLeaf);
		if(data < _key_tmp)	{	_pOldLeaf ->Insert(_leafdata);	}
		else				{	_pNewLeaf ->Insert(_leafdata);	}

		mItnlNode * _pFather = (mItnlNode*)(_pOldLeaf ->getFather());

		if(_pFather == NULL)
		{
//			_pOldLeaf��ǰ�Ǹ��ڵ㣬Ҫ��offset = 0 �ó���
//			������ռ������������������Ҫ�ͷ������
//			if(!preModified)
//			{
//				DelDisk(mfp, 0l, mblockQueue);
//			}
			long long int _addr_new = mblockQueue.Pop();
			_pOldLeaf ->setAddrFB(_addr_new);
//			setmodified in initial;
			mItnlNode * _pItnl = new mItnlNode;
	//		�����µ��׵�ַ
			long long int _addr_root = 0;
			long long int _addr_2 = _pNewLeaf ->getAddrFB();
			long long int _addr_1 = _pOldLeaf ->getAddrFB();
			KeyType & _key_1 = _pOldLeaf ->LeafData[1].mData;
			KeyType & _key_2 = _pNewLeaf ->LeafData[1].mData;

			_pOldLeaf ->setFather(_pItnl);
			_pNewLeaf ->setFather(_pItnl);
			_pItnl ->setAddrFB(_addr_root);
			_pItnl ->setCount(2);
			_pItnl ->setPointer(1, _pOldLeaf);
			_pItnl ->setPointer(2, _pNewLeaf);
			_pItnl ->setKey(1, _key_1);
			_pItnl ->setKey(2, _key_2);
			_pItnl ->setSonAddr(1, _addr_1);
			_pItnl ->setMemory(1);
			_pItnl ->setMemory(2);
			_pItnl ->setSonAddr(2, _addr_2);
			this ->setRoot(_pItnl);
			return true;
		}
		else
		{
			bool _ret = InsertItnlNode(_pFather, _pNewLeaf);
			return _ret;
		}
	}
	return false;
}
/* dupInsert will replace previous value */
bool mLeafNode :: dupInsert(const mleafdata & _mleafdata, int _index_insert)
{

	mleafdata & _tmp_leafdata = (this ->getElement(_index_insert));

	_tmp_leafdata = _mleafdata;

	return true;
}

/* ɾ��ĳ����
 * �漰ɾ���ڵ�ʱע��������~~
*/
bool BPlusTree::Delete(KeyType & data)
{
	mLeafNode * _pOldLeaf = SearchLeafNode(data);
	// for when _ikey = 1
	//if ok , return the index of the deleted
	//���idelete��1�Ļ���������Ƿ��������ɾ��  ����
	int _idelete = _pOldLeaf ->Delete(data);
	if(_idelete < 0)	return false;

	mItnlNode * _pFather = (mItnlNode* )(_pOldLeaf ->getFather());
	if(_pFather == NULL)
	{
		return true;
	}

	if(_pOldLeaf ->getCount() >= ORDER_V)
	{
		//���idelete = 1 ����ɾ��  ����Ҫ
		return true;
	}

	// count < 50%
	int flag = FLAG_LEFT;
	// ���ֵ�����
	mLeafNode * _pBrother = (mLeafNode*)(_pOldLeaf ->getBrother(flag));

	//brother > 50%
	if(_pBrother ->getCount() > ORDER_V)
	{
		if(FLAG_LEFT == flag)
		{
			mleafdata  & _leafdata = _pBrother ->getElement(_pBrother ->getCount() );
			KeyType & _key = _leafdata.mData;
			_pOldLeaf ->Insert(_leafdata);
			_pBrother ->Delete(_key);
		}
		else
		{
			mleafdata  & _leafdata = _pBrother ->getElement(1 );
			KeyType & _key = _leafdata.mData;
			_pOldLeaf ->Insert(_leafdata);
			_pBrother ->Delete(_key);
		}
		return true;
	}

	// combine
	if(FLAG_LEFT == flag)
	{
		_pBrother ->Combine(_pOldLeaf);
		KeyType & _key = _pOldLeaf ->getKey(1);
		bool dRet =  this ->DeleteItnlNode(_pFather, _key);
		DelDisk(this ->mfp, _pOldLeaf ->getAddrFB(), this ->mblockQueue);
		this ->mblockQueue.Push(_pOldLeaf ->getAddrFB());
		delete _pOldLeaf;
		return dRet;
	}
	else
	{
		_pOldLeaf ->Combine(_pBrother);
		KeyType & _key = _pBrother ->getKey(1);
		bool dRet =  this ->DeleteItnlNode(_pFather, _key);
		DelDisk(this ->mfp, _pBrother ->getAddrFB(), this ->mblockQueue);
		this ->mblockQueue.Push(_pBrother ->getAddrFB());
		delete _pBrother;
		return dRet;
	}

	cout << "bug run" << endl;
	return false;
}
//����ɾ������
bool BPlusTree :: Delete(KeyType & data, char PartVal[])
{
	mLeafNode * _pOldLeaf = SearchLeafNode(data);
	// for when _ikey = 1
	//if ok , return the index of the deleted
	//���idelete��1�Ļ���������Ƿ��������ɾ��  ����
	int pvFlag = FLAG_ZERO;
	int _idelete = _pOldLeaf ->Delete(data, PartVal, pvFlag);
	if(_idelete < 0)	return false;
	if(pvFlag == FLAG_NO_ZERO) return true;

	mItnlNode * _pFather = (mItnlNode* )(_pOldLeaf ->getFather());
	if(_pFather == NULL)
	{
		return true;
	}

	if(_pOldLeaf ->getCount() >= ORDER_V)
	{
		//���idelete = 1 ����ɾ��  ����Ҫ
		return true;
	}

	// count < 50%
	int flag = FLAG_LEFT;
	// ���ֵ�����
	mLeafNode * _pBrother = (mLeafNode*)(_pOldLeaf ->getBrother(flag));

	//brother > 50%
	if(_pBrother ->getCount() > ORDER_V)
	{
		if(FLAG_LEFT == flag)
		{
			mleafdata  & _leafdata = _pBrother ->getElement(_pBrother ->getCount() );
			KeyType & _key = _leafdata.mData;
			_pOldLeaf ->Insert(_leafdata);
			_pBrother ->Delete(_key);
		}
		else
		{
			mleafdata  & _leafdata = _pBrother ->getElement(1 );
			KeyType & _key = _leafdata.mData;
			_pOldLeaf ->Insert(_leafdata);
			_pBrother ->Delete(_key);
		}
		return true;
	}

	// combine
	if(FLAG_LEFT == flag)
	{
		_pBrother ->Combine(_pOldLeaf);
		KeyType & _key = _pOldLeaf ->getKey(1);
		bool dRet =  this ->DeleteItnlNode(_pFather, _key);
		DelDisk(this ->mfp, _pOldLeaf ->getAddrFB(), this ->mblockQueue);
		this ->mblockQueue.Push(_pOldLeaf ->getAddrFB());
		delete _pOldLeaf;
		return dRet;
	}
	else
	{
		_pOldLeaf ->Combine(_pBrother);
		KeyType & _key = _pBrother ->getKey(1);
		bool dRet =  this ->DeleteItnlNode(_pFather, _key);
		DelDisk(this ->mfp, _pBrother ->getAddrFB(), this ->mblockQueue);
		this ->mblockQueue.Push(_pBrother ->getAddrFB());
		delete _pBrother;
		return dRet;
	}

	cout << "bug run" << endl;
	return false;
	return false;
}
void BPlusTree::Flush(){
	this ->StoreTree();
	this ->ClearTree();
}
// �����������ɾ�����н��
void BPlusTree :: ClearTree()
{
	queue<mNode *> pQueue[100];
	stack<mNode *> pStack;
	int nFloor = 0;
	mNode * pRoot = this ->getRoot();
	if(pRoot == NULL)	return;
	mNode * pNode;
	pQueue[nFloor].push(pRoot);
	pStack.push(pRoot);
	//printf("\n\nthe %d floor:\n\n", nFloor + 1);
	while(!pQueue[nFloor].empty())
	{
		pNode = pQueue[nFloor].front();
		pQueue[nFloor].pop();

		if(pNode ->getType()  == NODE_TYPE_INTERNAL)
		{
			for(int i = 1; i <= pNode ->getCount(); i ++)
			{
				if(pNode ->isInMemory(i))
				{
					pQueue[nFloor + 1].push(pNode ->getPointer(i));
					pStack.push(  pNode ->getPointer(i)  );
				}
			}
		}
		if(pQueue[nFloor].empty())
		{
			nFloor ++;
		}
	}

	//cout << "delete node" << endl;

	int _n_node = 0;

	while(!pStack.empty())
	{
		pNode = pStack.top();
		pStack.pop();
		delete pNode;
		_n_node ++;
		pNode = NULL;
		if(_n_node % 400 == 0)
		{
			//cout << "_delete_node: " << _n_node << "   ";
		}
	}
	if(_n_node > 1)
	{
		cout << "clear end " << this ->getTreeFileName().c_str() << endl;
	}
	this ->setRoot(NULL);
	fclose(this ->mfp);
	return;
}

// ������Ƿ�����B+���Ķ���
//bool BPlusTree::CheckTree()
//{}

// �ݹ����㼰�������Ƿ�����B+���Ķ���
//bool BPlusTree::CheckNode(mNode* pNode)
//{}

// ��ӡ������
//void BPlusTree::PrintTree(FILE * ifp)
//{}

// ��ӡĳ���
//void BPlusTree::PrintNode(mNode* pNode, FILE * ifp)
//{}



//�ݹ麯������������м���
//key��ΪpNode�е��׸�key
bool BPlusTree::InsertItnlNode(mItnlNode* pNode, mNode* pSon)
{
	if(pNode == NULL || pNode ->getType() == NODE_TYPE_LEAF)
	{
		return false;
	}

	KeyType data;
	if(pSon ->getType() == NODE_TYPE_LEAF)
	{
		data = ((mLeafNode*)pSon) ->LeafData[1].mData;
	}
	else
	if(pSon ->getType() == NODE_TYPE_INTERNAL)
	{
		data = ((mItnlNode*)pSon) ->ItnlData[1].mKey;
	}
	else
	{
		printf("err in pson\n");
		system("pause"); exit(0);
	}

	if(pNode ->getCount() < MAXNUM_KEY)
	{
//		setmodified in insert;
		if(!pNode ->getModify())
		{
			DelDisk(mfp, pNode ->getAddrFB(), mblockQueue);
		}
		bool _pI_Ret;
		_pI_Ret = pNode ->Insert(pSon);
	}
	else
	{
		mItnlNode * _pOldItnl = pNode;
//		setmodified in mnode_intial;
		mItnlNode * _pNewItnl = new mItnlNode;
		long long int _addr_newitnl = mblockQueue.Pop();
		_pNewItnl ->setAddrFB(_addr_newitnl);
		if(!pNode ->getModify())
		{
			DelDisk(mfp, pNode ->getAddrFB(), mblockQueue);
		}
		KeyType & _key_tmp = _pOldItnl ->Split(_pNewItnl);

		if(_key_tmp > data)
		{
			_pOldItnl ->Insert(pSon);
		}
		else
		{
			_pNewItnl ->Insert(pSon);
		}

		mItnlNode * _pFather = (mItnlNode *)(_pOldItnl ->getFather());

		if(_pFather == NULL)
		{
//			ԭoffset = 0�����Լ���Ӧ�������ӿ������
//			�ж��Ƿ���Ҫɾ���������
//			if(!preModified)
//			{
//				DelDisk(mfp, 0l, mblockQueue);
//			}
			int _look_;
			_look_ = _ii;
			long long int _addr_new = mblockQueue.Pop();
			_pOldItnl ->setAddrFB(_addr_new);
//			setmodified in mnode_initial;
			mItnlNode * _pItnl = new mItnlNode;
	//		�����µ��׵�ַ
			long long int _addr_root = 0l;
			long long int _addr_1 = _pOldItnl ->getAddrFB();
			long long int _addr_2 = _pNewItnl ->getAddrFB();
			KeyType & _key_1 = _pOldItnl ->ItnlData[1].mKey;
			KeyType & _key_2 = _pNewItnl ->ItnlData[1].mKey;

			_pOldItnl ->setFather(_pItnl);
			_pNewItnl ->setFather(_pItnl);
			_pItnl ->setAddrFB(_addr_root);
			_pItnl ->setCount(2);
			_pItnl ->setPointer(1, _pOldItnl);
			_pItnl ->setPointer(2, _pNewItnl);
			_pItnl ->setKey(1, _key_1);
			_pItnl ->setKey(2, _key_2);
			_pItnl ->setSonAddr(1, _addr_1);
			_pItnl ->setSonAddr(2, _addr_2);
			_pItnl ->setMemory(1);
			_pItnl ->setMemory(2);
			this ->setRoot(_pItnl);
			return true;
		}
		else
		{
			bool _ret = InsertItnlNode(_pFather, _pNewItnl);
			return _ret;
		}
	}
	return false;
}
/*
 * ɾ��key��Ӧ��Ԫ�ز���delete��������ɶԸ��ڵ���޸ģ� ע���ڴ�λ��ͬ���޸�
 * ���ڵ� > 50% ��Ϊ���ڵ㣬 �����
 *
 */
// �ݹ麯�������м�����ɾ����
bool BPlusTree::DeleteItnlNode(mItnlNode* pItnl, KeyType & key)
{
	int _idelete = pItnl ->Delete(key);
	if(_idelete < 0)
	{
		cout << "bug idelete" << endl;
		system("pause"); exit(0);
	}

	mItnlNode * _pFather = (mItnlNode*)(pItnl ->getFather());
	if(_pFather == NULL || pItnl ->getCount() > ORDER_V)
	{
		return true;
	}
	int flag = FLAG_LEFT;
	mItnlNode * _pBrother = (mItnlNode *)(pItnl ->getBrother(flag));
	// brother > 50%
	if(_pBrother ->getCount() > ORDER_V)
	{
		if(FLAG_LEFT == flag)
		{
			mitnldata & _itnldata = _pBrother ->getElement(_pBrother ->getCount() );
			pItnl ->Insert(_itnldata.mPointer);// maybe have bug~~~~~
			_pBrother ->Delete(_itnldata.mKey);
		}
		else
		{
			mitnldata & _itnldata = _pBrother ->getElement(1);
			pItnl ->Insert(_itnldata.mPointer);// maybe have bug~~~~~
			_pBrother ->Delete(_itnldata.mKey);
		}
		return true;
	}

	// brother = 50%  combine
	if(FLAG_LEFT == flag)
	{
		_pBrother ->Combine(pItnl);
		KeyType & _key = pItnl ->getKey(1);
		bool dRet = this ->DeleteItnlNode(_pFather, _key);
		DelDisk(this ->mfp, pItnl ->getAddrFB(), this ->mblockQueue);
		this ->mblockQueue.Push(pItnl ->getAddrFB());
		delete pItnl;
		return dRet;
	}
	else
	{
		pItnl ->Combine(_pBrother);
		KeyType & _key = _pBrother ->getKey(1);
		bool dRet = this ->DeleteItnlNode(_pFather, _key);
		DelDisk(this ->mfp, _pBrother ->getAddrFB(), this ->mblockQueue);
		this ->mblockQueue.Push(_pBrother ->getAddrFB());
		delete _pBrother;
		return dRet;
	}
	cout << "run bug" << endl;
	return false;
}
//�������ṹ
/*
 * ��֤���㣺
 * 1���ڴ�λ��Ƕ���ȷ
 * 2���޸�λ��Ƕ���ȷ
 */
void BPlusTree :: StoreTree()
{
	mNode * pRoot = this ->getRoot();
	FILE * fp = this ->mfp;
	queue<mNode*> pQueue;
	pQueue.push(pRoot);
	mNode * pNode;
	int _i_ord = 0;
	bool any = false;
	//cout << "in store " << endl;
	while(!pQueue.empty())
	{
		pNode = pQueue.front();
		pQueue.pop();
//		����unmodify
		WriteNode(pNode, fp, this ->mblockQueue);
		if(pNode->getModify()){
			any = true;
		}
		_i_ord ++;
		if(_i_ord % 1600 == 0)
			cout << " - _i_ord= " << _i_ord;

		if(pNode ->getType() == NODE_TYPE_INTERNAL)
		{
			mItnlNode * pItnl = (mItnlNode *)pNode;
			for(int i = 1; i <= pNode ->getCount(); i ++)
			{
				if(pItnl ->isInMemory(i))
				{
					pQueue.push(pItnl ->getPointer(i));
				}
			}
		}
	}
	cout << endl;
	char _queuefile[50];
	strcpy(_queuefile, mTreeName);
	strcat(_queuefile, "_queue.btree");
	this ->mblockQueue.WriteQueue(_queuefile);
	fflush(this ->mfp);
	fflush(this ->mfp);
	if(any)
	{
		cout << "store end " << this ->getTreeFileName().c_str() << endl;
	}
}

//
//��ӡ��
void BPlusTree :: PrintTree()
{
	queue<mNode *> pQueue[100];
	int nFloor = 0;
	mNode * pRoot = this ->getRoot();
	if(pRoot == NULL)
	{
		cout << "root null" << endl;
		return;
	}
	mNode * pNode;
	pQueue[nFloor].push(pRoot);
	int fThreshold;
	cout << "input the floor threshold" << endl;
	scanf("%d", & fThreshold);
	printf("\n\nthe %d floor:\n\n", nFloor + 1);
	int _i_ord = 0;
	while(!pQueue[nFloor].empty() && nFloor < fThreshold)
	{
		pNode = pQueue[nFloor].front();
		pQueue[nFloor].pop();
		pNode ->printNode();
		cout << "##" << _i_ord ++ << "## ";

		if(pNode ->getType()  == NODE_TYPE_INTERNAL)
		{
			for(int i = 1; i <= pNode ->getCount(); i ++)
			{
				if(pNode ->isInMemory(i))
				{
					pQueue[nFloor + 1].push(pNode ->getPointer(i));
				}
			}
		}
		if(pQueue[nFloor].empty())
		{
			nFloor ++;
			printf("\n\nthe %d floor:\n\n", nFloor + 1);
		}
	}
}

/*
 * �½��ڵ���Ҫ�ṩ����Ϣ��
 *     �ڵ���׿��ַ
 *     ����type int
 *     ����count int
 *     ����count_block int
 *     ����blocklink mBlockLink
 *
 *     ������Ԫ�غ� ͨ���¿��ַת�ƣ� ת�Ժ�����Ԫ�ظ����� �ٶ��������
 *
 */

mNode * ReadNode(FILE * fp, long long _addrfb)//ÿ���½��Ľڵ㶼�з���Ļ��ϲ�ڵ������׿�洢����ַ
{
	fseek(fp, _addrfb, SEEK_SET);
	int _type_tmp;
	int _count_tmp;
	int _count_block_ele;
	mBlockLink _curblocklink;
	fread(&_type_tmp, sizeof(_type_tmp), 1, fp);
	fread(&_count_tmp, sizeof(_count_tmp), 1, fp);
	fread(&_count_block_ele, sizeof(_count_block_ele), 1, fp);
	fread(&_curblocklink, sizeof(_curblocklink), 1, fp);
	int size_int = sizeof(int);
	int size_blocklink = sizeof(mBlockLink);

	NODE_TYPE _nodetype = (NODE_TYPE)_type_tmp;

	int _i_tmp = 1;
	if(_nodetype == NODE_TYPE_LEAF)
	{
		mLeafNode * _pLeaf = new mLeafNode;
		_pLeaf ->setCount(_count_tmp);
		_pLeaf ->unModify();
		_pLeaf ->setAddrFB(_addrfb);
		fread(&(_pLeaf ->leafLink), sizeof(_pLeaf ->leafLink), 1, fp);
		/*
		 * while cycle��
		 *  for cycle
		 *  ͨ������Ԫ�ظ�������
		 */

		/*
		 * ����� �ȼ�¼��ǰ�����ڵ�ĵڼ���Ԫ��
		 * �ļ�ָ��ƫ����ָʾ����һ��
		 * �ٶ������Ԫ�ظ��������¿�ṹ�����
		 * �������룬 ֱ��Ԫ�ظ����ﵽcountֵ
		 */
		/*
		 * �Ȱѿ��ʣ��ռ�д�� -1�� ��д��len������׼ȷ����ռ䣩�� sizeleft ��ȥ����4��12�ֽڣ� ��-1����len����sizeleft��������
		 * д��sizeleft������ʱ��Ҫ�ֶζ��롡��Ȼ������飬���ڽ�������д��֮ǰλ��
		 * д��ʣ��Ŀռ�� ����buffer����size
		 * Ȼ��ÿ������һ����������һ�������Լ������ӽṹ��Ĵ�С�����Ա�д�뵱ǰ���ŵĳ���buffer(�������һ��ô���)���Լ�������
		 * д��ʣ���buffer���д���ȼ������ӣ� �������һ�飬 Ҫע������ fpָ�� & sizeleft��
		 */
		bool ReadIn = true;
		while(_i_tmp <= _count_tmp)
		{
			for(int i = 0; i < _count_block_ele; i ++)
			{
				ReadIn = _pLeaf ->LeafData[_i_tmp].Read_mleafdata(fp);
				if(!ReadIn)
				{
					int _size_buffer = 0;
					int _len = 0;
					int _size_left = 0;
					int _size_inBlock = 0;
					_pLeaf ->LeafData[_i_tmp].pVal = new mValue;
					fread(&_len, size_int, 1, fp);
					_size_buffer = _len + 1;
					char * _buffer = new char[_size_buffer];
					_pLeaf ->LeafData[_i_tmp].pVal ->Term[0] = _buffer;
					_pLeaf ->LeafData[_i_tmp].pVal ->lenTerm[0] = _len;
					fread(&_size_left, size_int, 1, fp);
					fread(_buffer, sizeof(char), _size_left, fp);
					_buffer += _size_left;
					_size_buffer -= _size_left;
					while(_size_buffer > 0)
					{
						fseek(fp, _curblocklink.nextBlockAddr, SEEK_SET);
						fread(&_size_inBlock, sizeof(_size_inBlock), 1, fp);
						fread(&_curblocklink, size_blocklink, 1, fp);
						fread(_buffer, sizeof(char), _size_inBlock, fp);
						_buffer += _size_inBlock;
						_size_buffer -= _size_inBlock;
					}
					if(_size_buffer != 0)
					{
						cout << "size buffer" << endl;
						system("pause"); exit(0);
					}
				}
				_pLeaf ->setMemory(_i_tmp);
				_i_tmp ++;
			}
//			printf("_i_tmp :read = %d, in count: %d\n", _i_tmp, _count_tmp);

			if(_curblocklink.nextBlockAddr < 0 && _i_tmp < _count_tmp)
			{
				printf("err in nextblockaddr of readnode()");
				system("pause"); exit(0);
			}
			if(_i_tmp > _count_tmp)	break;
//			cout << "nextblockaddr: " << _curblocklink.nextBlockAddr << endl;
			fseek(fp, _curblocklink.nextBlockAddr, SEEK_SET);
			fread(&_count_block_ele, sizeof(_count_block_ele), 1, fp);
			fread(&_curblocklink, size_blocklink, 1, fp);
		}

		return _pLeaf;
	}
	else
	if(_nodetype == NODE_TYPE_INTERNAL)
	{
		mItnlNode * _pItnl = new mItnlNode;
		_pItnl ->setCount(_count_tmp);
		_pItnl ->unModify();
//		��ӣ� δ֪֮ǰû�����ַ��ԭ��
		_pItnl ->setAddrFB(_addrfb);
		while(_i_tmp <= _count_tmp)
		{
			for(int i = 0; i < _count_block_ele; i ++)
			{
				_pItnl ->ItnlData[_i_tmp].Read_mitnldata(fp);
				_i_tmp ++;
			}
//			printf("_i_tmp read = %d, in count: %d\n", _i_tmp, _count_tmp);

			if(_curblocklink.nextBlockAddr < 0 && _i_tmp < _count_tmp)
			{
				printf("err in nextblockaddr of readnode()");
				system("pause"); exit(0);
			}
//			cout << "nextblockaddr: " << _curblocklink.nextBlockAddr << endl;
			fseek(fp, _curblocklink.nextBlockAddr, SEEK_SET);
			fread(&_count_block_ele, sizeof(_count_block_ele), 1, fp);
			fread(&_curblocklink, sizeof(_curblocklink), 1, fp);
		}
		return _pItnl;
	}
	else
	{
		printf("err in readnode of type\n");
		system("pause"); exit(0);
	}
	return NULL;
}

void WriteNode(mNode * pNode, FILE * fp, mQueue & _mqueue)
{
	if(!pNode ->getModify())		return;
	long long int _addrfb = pNode ->getAddrFB();
//	for check
//	printf("addr write : %lld\n", _addrfb);
	if(_addrfb < 0)
	{
		printf("err in setAddrFB\n");
		system("pause"); exit(0);
	}

	pNode ->unModify();

	int _size_left = BLOCKSIZE;
	//cout << "size_left1" << _size_left << endl;

	fseek(fp, _addrfb, SEEK_SET);
	int size_nodetype = sizeof(NODE_TYPE_LEAF);
	int size_count = sizeof(pNode ->getCount());
	int size_int   = sizeof(int);
	int size_lli   = sizeof(long long int);
	int size_blocklink = sizeof(mBlockLink);//-----------------16

	int _type_tmp = (int)pNode ->getType();
	int _count_tmp = pNode ->getCount();

	fwrite(&(_type_tmp),  size_nodetype, 1, fp);
	_size_left -= size_nodetype;//-----------------------------int
	fwrite(&(_count_tmp), size_count, 1, fp);
	_size_left -= size_count;//--------------------------------int

	long long int _addr_blocklink = ftell(fp);   // ���ܲ�������
	fseek(fp, size_int + size_blocklink, SEEK_CUR);
	_size_left -= size_int + size_blocklink;//------------------int + long_long_int*2

	//cout << "size_left2" << _size_left << endl;
	if(pNode ->getType() == NODE_TYPE_LEAF)
	{
		mLeafNode * _pLeaf = (mLeafNode *)pNode;
		int _count = _pLeaf ->getCount();

		fwrite(&(_pLeaf ->leafLink), sizeof(_pLeaf ->leafLink), 1, fp);
		_size_left -= sizeof(_pLeaf ->leafLink);//--------------long_long_int*2

		int _i_tmp = 1;
		bool bool_WriteIn;
		int nEle_inBlock = 0;
		int first_int = 0;
		long long int _preblockaddr = -1;
		long long int _curblockaddr = _addrfb;
		mBlockLink _blocklink;
		for(; _i_tmp <= _count; _i_tmp ++)
		{
			/*
			 * ����ʣ����С�� ����ǰԪ���ܹ�����д����д�벢����true�� ����д�벢����false;
			 * �������false���ȷ�д����Ԫ�ظ��� �����¿����ϵ_  _addr_blocklink��
			 * �������¿鲢����д�룺 �ָ�_size_left, д��mblocklink
			 * �޸����¿�����
			 * �ĳɿ���Ԫ�ظ�������
			 * �����ļ�ָ��, ����Ԫ�ع���
			 */
			int size_key = -1;
			int size_val = -1;
			int _tmp_i   = -1;

			bool_WriteIn = _pLeaf ->LeafData[_i_tmp].Write_mleafdata(fp, _size_left, size_key, size_val);
			if(!bool_WriteIn)   //ȷ���������е�һԪ�س���4K�� ���ܲ�������
			{
				if(size_key + size_val > BLOCKSIZE - size_int*3 - size_lli*4
				   && _size_left > size_key + size_int * 3 + 1)
				{
					_pLeaf ->LeafData[_i_tmp].mData.WriteKey(fp);
					_size_left -= size_key;
					fwrite(&_tmp_i, sizeof(int), 1, fp);
					_size_left -= size_int;
					int val_len = _pLeaf ->LeafData[_i_tmp].pVal ->lenTerm[0];
					fwrite(&val_len, sizeof(int), 1, fp);
					_size_left -= size_int;

					_size_left -= size_int + 1;// for safety
					fwrite(&_size_left, sizeof(int), 1, fp);

					char * _term_buffer = _pLeaf ->LeafData[_i_tmp].pVal ->Term[0];
					int  _size_buffer = val_len;

					fwrite(_term_buffer, sizeof(char), _size_left, fp);
					_size_buffer -= _size_left;
					_term_buffer += _size_left;

//					_preblockaddr = _curblockaddr;
//					_curblockaddr = _mqueue.Pop();
					_blocklink.mBlockLink_Initial();
					_blocklink.preBlockAddr = _preblockaddr;
					_preblockaddr = _curblockaddr;   // �¿����һ����ǵ�ǰ�飨�׿�ָ��-1��
					_curblockaddr = _mqueue.Pop();    //��ǰ������ٵ���Ϊָ���¿�
					_blocklink.nextBlockAddr = _curblockaddr;  // ��һ�����һ�鼴Ϊ�¿�

					fseek(fp, _addr_blocklink, SEEK_SET);
					nEle_inBlock ++;
					fwrite(&nEle_inBlock, size_int, 1, fp);
					nEle_inBlock = 0;
					fwrite(&_blocklink, size_blocklink, 1, fp);

					fseek(fp, _curblockaddr, SEEK_SET);
					_addr_blocklink = _curblockaddr;//������дƫ��
					fseek(fp, size_blocklink + size_int, SEEK_CUR);

					//write back blocklink

					int _block_hold = BLOCKSIZE - size_blocklink - size_int - 1;
					while(_size_buffer > _block_hold)
					{
						fwrite(_term_buffer, sizeof(char), _block_hold, fp);
						_term_buffer += _block_hold;
						_size_buffer -= _block_hold;

						_blocklink.mBlockLink_Initial();
						_blocklink.preBlockAddr = _preblockaddr;
						_preblockaddr = _curblockaddr;   // �¿����һ����ǵ�ǰ�飨�׿�ָ��-1��
						_curblockaddr = _mqueue.Pop();    //��ǰ������ٵ���Ϊָ���¿�
						_blocklink.nextBlockAddr = _curblockaddr;  // ��һ�����һ�鼴Ϊ�¿�

						fseek(fp, _addr_blocklink, SEEK_SET);
						fwrite(&_block_hold, size_int, 1, fp);
						fwrite(&_blocklink, size_blocklink, 1, fp);

						fseek(fp, _curblockaddr, SEEK_SET);
						_addr_blocklink = _curblockaddr;//������дƫ��
						fseek(fp, size_blocklink + size_int, SEEK_CUR);
					}

					// finish the left;
					_size_buffer ++;  // write size is len + 1;
					fwrite(_term_buffer, sizeof(char), _size_buffer, fp);
//					fseek(fp, _addr_blocklink, SEEK_SET);
//					fwrite(&_size_buffer, size_int, 1, fp);
//					fwrite(&_blocklink, size_blocklink, 1, fp);
//					fseek(fp, _addr_blocklink + _size_buffer + size_int + size_blocklink, SEEK_SET);
//					_size_left = BLOCKSIZE - _size_buffer - size_int - size_blocklink;
					_size_left = -1;
					first_int = _size_buffer;
					/*
					 * �Ȱѿ��ʣ��ռ�д�� -1�� ��д��len������׼ȷ����ռ䣩�� sizeleft ��ȥ����4��12�ֽڣ� ��-1����len����sizeleft��������
					 * д��sizeleft������ʱ��Ҫ�ֶζ��롡��Ȼ������飬���ڽ�������д��֮ǰλ��
					 * д��ʣ��Ŀռ�� ����buffer����size
					 * Ȼ��ÿ������һ����������һ�������Լ������ӽṹ��Ĵ�С�����Ա�д�뵱ǰ���ŵĳ���buffer(�������һ��ô���)���Լ�������
					 * д��ʣ���buffer���д���ȼ������ӣ� �������һ�飬 Ҫע������ fpָ�� & sizeleft��
					 */
				}
				else
				{
				_i_tmp --;
				_size_left = BLOCKSIZE;			//�ظ���������



				_blocklink.mBlockLink_Initial();
				_blocklink.preBlockAddr = _preblockaddr;
				_preblockaddr = _curblockaddr;   // �¿����һ����ǵ�ǰ�飨�׿�ָ��-1��
				_curblockaddr = _mqueue.Pop();    //��ǰ������ٵ���Ϊָ���¿�
				_blocklink.nextBlockAddr = _curblockaddr;  // ��һ�����һ�鼴Ϊ�¿�
				/*
				 * д�ؿ���Ԫ�ظ����Լ�������
				 */
				fseek(fp, _addr_blocklink, SEEK_SET);
				int size_ele_inblock = sizeof(nEle_inBlock);
				fwrite(&first_int, size_ele_inblock, 1, fp);
				fwrite(&_blocklink, size_blocklink, 1, fp);

				fseek(fp, _curblockaddr, SEEK_SET);
				_addr_blocklink = _curblockaddr;//������дƫ��
				fseek(fp, size_ele_inblock + size_blocklink, SEEK_CUR);
				_size_left -= size_ele_inblock + size_blocklink;//===========int + lli * 2

				nEle_inBlock = 0;
				}
			}
			else
			{
				nEle_inBlock ++;
				first_int = nEle_inBlock;
			}// if write_in

		}// for count
		/*
		 * ���һ��Ĵ���
		 */

		_blocklink.mBlockLink_Initial();
		_blocklink.preBlockAddr = _preblockaddr;
		_blocklink.nextBlockAddr = -1;  // ��һ�����һ�鼴Ϊ�¿�
		fseek(fp, _addr_blocklink, SEEK_SET);
		fwrite(&first_int, size_int, 1, fp);
		fwrite(&_blocklink, size_blocklink, 1, fp);
	}
	else
	if(pNode ->getType() == NODE_TYPE_INTERNAL)
	{
		mItnlNode * _pItnl = (mItnlNode *)pNode;
		int _count = _pItnl ->getCount();

		int _i_tmp = 1;
		bool bool_WriteIn;
		int nEle_inBlock = 0;
		long long int _preblockaddr = -1;
		long long int _curblockaddr = _addrfb;
		mBlockLink _blocklink;
		for(; _i_tmp <= _count; _i_tmp ++)
		{
			/*
			 * ����ʣ����С�� ����ǰԪ���ܹ�����д����д�벢����true�� ����д�벢����false;
			 * �������false���ȷ�д����Ԫ�ظ��� �����¿����ϵ_  _addr_blocklink��
			 * �������¿鲢����д�룺 �ָ�_size_left, д��mblocklink
			 * �޸����¿�����
			 * �ĳɿ���Ԫ�ظ�������
			 * �����ļ�ָ��, ����Ԫ�ع���
			 */
			bool_WriteIn = _pItnl ->ItnlData[_i_tmp].Write_mitnldata(fp, _size_left);
			if(!bool_WriteIn)   //ȷ���������е�һԪ�س���4K�� ���ܲ�������
			{
				_i_tmp --;
				_size_left = BLOCKSIZE;			//�ظ���������



				_blocklink.mBlockLink_Initial();
				_blocklink.preBlockAddr = _preblockaddr;
				_preblockaddr = _curblockaddr;   // �¿����һ����ǵ�ǰ�飨�׿�ָ��-1��
				_curblockaddr = _mqueue.Pop();    //��ǰ������ٵ���Ϊָ���¿�
				_blocklink.nextBlockAddr = _curblockaddr;  // ��һ�����һ�鼴Ϊ�¿�
				/*
				 * д�ؿ���Ԫ�ظ����Լ�������
				 */
				fseek(fp, _addr_blocklink, SEEK_SET);
				int size_ele_inblock = sizeof(nEle_inBlock);
				fwrite(&nEle_inBlock, size_ele_inblock, 1, fp);
				fwrite(&_blocklink, size_blocklink, 1, fp);

				fseek(fp, _curblockaddr, SEEK_SET);
				_addr_blocklink = _curblockaddr;//������дƫ��
				fseek(fp, size_ele_inblock + size_blocklink, SEEK_CUR);
				_size_left -= size_ele_inblock + size_blocklink;

				nEle_inBlock = 0;
			}
			else
			{
				nEle_inBlock ++;
			}
		}
		/*
		 * ���һ��Ĵ���
		 */

		_blocklink.mBlockLink_Initial();
		_blocklink.preBlockAddr = _preblockaddr;
		_blocklink.nextBlockAddr = -1;  // ��һ�����һ�鼴Ϊ�¿�
		fseek(fp, _addr_blocklink, SEEK_SET);
		int size_ele_inblock = sizeof(nEle_inBlock);
		fwrite(&nEle_inBlock, size_ele_inblock, 1, fp);
		fwrite(&_blocklink, size_blocklink, 1, fp);
	}
	else
	{
		printf("err in nodetype\n");
	}
}

void DelDisk(FILE * fp, long long int _addrfb, mQueue & _mqueue)
{
	fseek(fp, _addrfb, SEEK_SET);
//	cout << "Del" << _addrfb << endl;
	int _type_tmp;
	int _count_tmp;
	int _count_block_ele;
	mBlockLink _curblocklink;
	fread(&_type_tmp, sizeof(_type_tmp), 1, fp);
	fread(&_count_tmp, sizeof(_count_tmp), 1, fp);
	fread(&_count_block_ele, sizeof(_count_block_ele), 1, fp);
	fread(&_curblocklink, sizeof(_curblocklink), 1, fp);

	long long int _cur_addr = 0;
	int _i_tmp = 0;
	long long int BackAddr[1000] = {};
	vector<long long int> BackVec;
//	BackAddr[_i_tmp] = _addrfb;
//	_i_tmp ++;				�׿��ַ����Ҫһ����գ� ��deleteʵ��֮���׿��ַ����ʱpush�ģ���
	while(_curblocklink.nextBlockAddr != -1)
	{
		{
			BackVec.push_back(_curblocklink.nextBlockAddr);
			_cur_addr = _curblocklink.nextBlockAddr;
			fseek(fp, _cur_addr, SEEK_SET);
			fread(&_count_block_ele, sizeof(_count_block_ele), 1, fp);
			fread(&_curblocklink, sizeof(_curblocklink), 1, fp);
		}
//		BackAddr[_i_tmp] = _curblocklink.nextBlockAddr;
//		_i_tmp ++;
//		_cur_addr = _curblocklink.nextBlockAddr;
//		fseek(fp, _cur_addr, SEEK_SET);
//		fread(&_count_block_ele, sizeof(_count_block_ele), 1, fp);
//		fread(&_curblocklink, sizeof(_curblocklink), 1, fp);
////		for check
//		if(_i_tmp <= 0 || _i_tmp > 1000000)
//		{
//			printf("bug in _i_tmp\n");
//			system("pause"); exit(0);
//		}
	}
	_mqueue.MulPush(BackVec);
}
int myStrcmp(char _str1[], int len1, char _str2[], int len2)
{
	int minlen = len1;
	int maxlen = len2;
	if(len1 > len2)
	{
		minlen = len2;
		maxlen = len1;
	}
	int i = 0;
	for(; i < minlen; i ++)
	{
		if(_str1[i] < _str2[i]) return -1;
		if(_str1[i] > _str2[i]) return 1;
	}

	if(len1 > len2) return 1;
	if(len1 < len2) return -1;
	return 0;
}




bool Delete_KeyVal(char keyStr[], int keyLen, BPlusTree * _ptree)
{
	KeyType _key_del;
	_key_del.set_sKey(keyStr, keyLen);
	bool dRet = _ptree ->Delete(_key_del);
	return dRet;
}

bool Delete_Key_PartVal(char keyStr[], int keyLen, char partVal[], BPlusTree * _ptree)
{
	KeyType _key_del;
	_key_del.set_sKey(keyStr, keyLen);
	bool dRet = _ptree ->Delete(_key_del, partVal);
	return dRet;
}

// ����Ϊ�ĸ���Ӧ��ɾ��ʵ�֣� ��������������������
bool Delete_sID2sub(int _sID, BPlusTree * _p_sID2sub)
{
	char * sid2str = new char[5];
	*(int*)sid2str = _sID;
	sid2str[4] = '\0';
	bool bret = Delete_KeyVal(sid2str, 4, _p_sID2sub);
	delete [] sid2str;
	return bret;
}
bool Delete_s2sID(char _sub_str[], BPlusTree * _p_s2sID)
{
	bool bret = Delete_KeyVal(_sub_str, (int)strlen(_sub_str), _p_s2sID);
	return bret;
}
bool Delete_obj2sID(char _obj_str[], int _del_sID, BPlusTree * _p_obj2sID)
{
	char * sid2str = new char[5];
	*(int*)sid2str = _del_sID;
	sid2str[4] = '\0';
	bool bret = Delete_Key_PartVal(_obj_str, (int)strlen(_obj_str), sid2str, _p_obj2sID);
	delete [] sid2str;
	return bret;
}
bool Delete_objpID2sID(char _obj_str[], int _pID, int _del_sID, BPlusTree * _p_obj2sID)
{
	char * sid2str = new char[5];
	char * pid2str = new char[5];
	int obj_len = (int)strlen(_obj_str);
	*(int*)sid2str = _del_sID;
	*(int*)pid2str = _pID;
	pid2str[4] = '\0';
	sid2str[4] = '\0';
	char * _objpID_str = new char[obj_len + 5];
	memcpy(_objpID_str, _obj_str, obj_len);
	memcpy(_objpID_str + obj_len, pid2str, 5);
	bool bret = Delete_Key_PartVal(_objpID_str, obj_len + 4, sid2str, _p_obj2sID);
	delete [] sid2str;
	delete [] pid2str;
	delete [] _objpID_str;
	return bret;
}

bool DATAINPUT(FILE * ifp, char _row_str[], char _str[][600] )
{
		memset(_row_str, 0, sizeof(_row_str));
		for(int i = 0; i < 6; i ++)
		{
			memset(_str[i], 0, sizeof(_str[i]));
		}
		fgets(_row_str, 5000, ifp);
		if(feof(ifp) || (int)strlen(_row_str) == 0) 	return false;
		int _row_len = (int)strlen(_row_str);
		int _nTab = 0;
		int _ri = 0;
		for(_nTab = 0; _nTab < 5; _nTab ++)
		{
			int j = _ri;
			while(_row_str[_ri] != '	')
			{
				_str[_nTab][_ri - j] = _row_str[_ri];
				_ri ++;
			}
			_str[_nTab][_ri - j] = '\0';
			_ri ++;
		}
		//_ri ++;  // NO  another tab
		for(int i = _ri; i < _row_len; i ++)
		{
			_str[5][i - _ri] = _row_str[i];
		}
	    int len5;
	    len5 = (int)strlen(_str[5]);
	    if(_str[5][len5 -1] == '\n')    {	    	_str[5][len5 - 1] = '\0';	    }
	    if(_str[5][len5 - 2] == '\t')	{	    	_str[5][len5 - 2] = '\0';	    }
		return true;
}

void FP_Initial(FILE * & _fp)
{
	if((_fp = fopen("sixtriples_yago", "rt")) == NULL)  //sixtriples_yago
	{
		cout << "bug" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		cout << "open successfully" << endl;
	}
	return;
}


void KeyType::ReadKey(FILE * fp)
{
	fread(&mLenKey, sizeof(int), 1, fp);
	if(_eletype == B_CHARARRAY)
	{
		sKey = new char[mLenKey + 1];
		fread(sKey, sizeof(char), mLenKey + 1, fp);
		if(sKey == NULL)
		{
			cout << "NULL err" << endl;
			system("pause"); exit(0);
		}

	}
	else
	{
		fread(&iKey, sizeof(int), 1, fp);
		sKey = NULL;
	}
}

void KeyType::WriteKey(FILE * fp)
{
	fwrite(&mLenKey, sizeof(int), 1, fp);
	if(_eletype == B_CHARARRAY)
	{
		fwrite(sKey, sizeof(char), mLenKey + 1, fp);
	}
	else
	{
		fwrite(&iKey, sizeof(int), 1, fp);
	}
}

void mValue::ReadVal(FILE * fp)
{
	fread(lenTerm, sizeof(int), TERM_NUMBER, fp);
	for(int i = 0; i < TERM_NUMBER; i ++)
	{
		if(Term[i] != NULL)
		{
			printf("bug term null\n");
			system("pause"); exit(0);
		}
		Term[i] = new char[ lenTerm[i] + 1 ];
		fread(Term[i], sizeof(char), lenTerm[i] + 1, fp);
	}
}
void mValue::WriteVal(FILE * fp)
{
	fwrite(lenTerm, sizeof(int), TERM_NUMBER, fp);
	for(int i = 0; i < TERM_NUMBER; i ++)
	{
		fwrite(Term[i], sizeof(char), lenTerm[i] + 1, fp);
	}
}

void mitnldata::Read_mitnldata(FILE * fp)
{
	fread(&mAddr_sonFB, sizeof(mAddr_sonFB), 1, fp);
	mKey.ReadKey(fp);
	return;
}
bool mitnldata::Write_mitnldata( FILE * fp, int & _size_left )
{
	/*
	 * KeyType ��Ҫ�ɺ�������д��Ŀռ��С
	 */
	int size_lli = sizeof(long long int);
	int size_mKey = mKey.WriteSize();
	if(_size_left < size_lli + size_mKey)		return false;

	_size_left -= size_lli + size_mKey;

	fwrite(&mAddr_sonFB, sizeof(mAddr_sonFB), 1, fp);
	mKey.WriteKey(fp);
	return true;
}

bool mleafdata::Read_mleafdata(FILE * fp)
{
	mData.ReadKey(fp);
	if(pVal != NULL)
	{
		printf("bug - null\n");
		system("pause"); exit(0);
	}
//		pVal ->ReadVal(fp);
	int _len=0;
	fread(&_len, sizeof(int), TERM_NUMBER, fp);
	if(_len == -1)
		return false;

	pVal = new mValue;
	for(int i = 0; i < TERM_NUMBER; i ++)
	{
		if(pVal ->Term[i] != NULL)
		{
			printf("bug term null\n");
			system("pause"); exit(0);
		}
		pVal ->Term[i] = new char[ _len + 1 ];
		pVal ->lenTerm[i] = _len;
		fread(pVal ->Term[i], sizeof(char), _len + 1, fp);
	}
	return true;
}
bool mleafdata::Write_mleafdata(FILE * fp, int & _size_left, int & _key_size, int & _val_size)
{
	int size_Key = mData.WriteSize();
	int size_Val = pVal ->WriteSize();
	//cout << "kv" << size_Key + size_Val << endl;
	if(_size_left < size_Key + size_Val)
	{
		_key_size = size_Key;
		_val_size = size_Val;
		return false;
	}
	_size_left -= size_Key + size_Val;

	mData.WriteKey(fp);
	pVal ->WriteVal(fp);
	return true;
}

void BPlusTree::Initial(){
	//return;
	this ->pmLeafHead = NULL;
	this ->pmLeafTail = NULL;
	mRoot = NULL;
	mfp = NULL;
}
BPlusTree::BPlusTree(const char * const_tree_name, const char * _build_or_open)
{
	{
		_log_btree = fopen("log_btree", "w+");
	}
	this ->Initial();
	insert_count = 0;
	char _tree_name[1000];
	memcpy(_tree_name, const_tree_name, (int)strlen(const_tree_name));
	_tree_name[(int)strlen(const_tree_name)] = '\0';
	int _key_chose;
	char treetype[200] = "initial";
	strcpy(mTreeName, _tree_name);
	_key_chose = 1;
	if(_key_chose == 1)
	{
		_eletype = B_CHARARRAY;
		strcpy(treetype, "char");
		//strcat(mTreeName, treetype);
	}
	else
	if(_key_chose == 2)
	{
		_eletype = B_INTEGER;
		strcpy(treetype, "int");
		strcat(mTreeName, treetype);
	}

	pmLeafHead = pmLeafTail = NULL;
	if(!strcmp(_build_or_open, "build"))
	{
		mblockQueue.Initial();
		mRoot = new mLeafNode;
		mRoot ->setAddrFB( 0 );
		printf("the tree called: %s\n", mTreeName);
		char _treefile[500];
		strcpy(_treefile, mTreeName);
		strcat(_treefile, ".btree");
		if((mfp = fopen(_treefile, "wb+")) == NULL)
		{
			printf("bug in create file\n");
			system("pause");
			exit(0);
		}
	}
	else
	{
		string _treefile = this ->getTreeFileName();
		_treefile += ".btree";
		while(true)
		{
			if((mfp = fopen(_treefile.c_str(), "rb+")) == NULL)
			{
				printf("err in open %s", mTreeName); cout << endl;
				system("pause"); exit(0);
			}
			else
			{
				mRoot = ReadNode(mfp, 0);
				if(mRoot == NULL){
					cout << "root of btree [" << _treefile <<  "] is NULL" << endl;
					exit(0);
				}
				break;
			}
		}
		char _queuefile[500];
		strcpy(_queuefile, mTreeName);
		strcat(_queuefile, "_queue.btree");
		mblockQueue.ReadQueue(_queuefile);
	}

}
BPlusTree::~BPlusTree()
{
	this ->ClearTree();
}
string BPlusTree::getTreeFileName(){
	string _tree_name = this ->mTreeName;
	return _tree_name;
}
void BPlusTree::log(const char* _log)const{
	bool debug_mode = true;
	if(!debug_mode) {
		return;
	}
	fputs(_log, _log_btree);
	fflush(_log_btree);
}
void BPlusTree::forcheck()
{
	queue<mNode *> pQueue[100];
		int nFloor = 0;
		mNode * pRoot = this ->getRoot();
		mNode * pNode;
		pQueue[nFloor].push(pRoot);
		int fThreshold;
		int _i_ord = 0;
		while(!pQueue[nFloor].empty() && nFloor < fThreshold)
		{
			pNode = pQueue[nFloor].front();
			pQueue[nFloor].pop();
			cout << _i_ord ++ << endl;

			if(pNode ->getType()  == NODE_TYPE_INTERNAL)
			{
				for(int i = 1; i <= pNode ->getCount(); i ++)
				{
					if(pNode ->isInMemory(i))
					{
						if(pNode != ((pNode ->getPointer(i)) ->getFather()))
						{
							cout << " bug " << _ii;
							cout << " bug key :   ";
							pNode ->getKey(i).PrintKey();
							cout << endl;
							system("pause"); exit(0);
						}
					}
				}
			}
			if(pQueue[nFloor].empty())
			{
				nFloor ++;
				printf("\n\nthe %d floor:\n\n", nFloor + 1);
			}
		}
}






