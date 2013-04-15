
/*
 * Entity.cpp
 */

#include "entity.h"
#include <iostream>

int Entity::s_id_gen = 0;

Entity::Entity() :
	m_id(s_id_gen++),
	m_pos(D3DXVECTOR3(0.0, 0.0, 0.0)),
	m_dir(D3DXVECTOR3(0.0, 0.0, 1.0)),
	m_type(ENTITY),
	m_ref(NULL)
{
}

Entity::Entity(D3DXVECTOR3 pos, D3DXVECTOR3 dir) : 
	m_id(s_id_gen++),
	m_pos(pos),
	m_dir(dir),
	m_type(ENTITY),
	m_ref(NULL)
{
}

string Entity::encode() const {
	char tmp[sizeof(Entity)] = {"\0"};
	//std::cerr << sizeof(Entity) << endl;
	tmp[0] = ENTITY;
	*(int *) (tmp + 1) = m_id;
	*(D3DXVECTOR3 *) (tmp + sizeof(m_id)) = m_pos;
	*(D3DXVECTOR3 *) (tmp + sizeof(D3DXVECTOR3) + sizeof(m_id)) = m_dir;
	return string(tmp);
}

Entity Entity::decode(string const &encoded) {
	const char* tmp = encoded.c_str();
	D3DXVECTOR3 m_pos_new( *(float*) (tmp + sizeof(m_id)), *(float*) (tmp + sizeof(m_id) + sizeof(float)), *(float*) (tmp + sizeof(m_id) + 2*sizeof(float)));
	int total = sizeof(m_id) + sizeof(D3DXVECTOR3);
	D3DXVECTOR3 m_dir_new( *(float*) (tmp + total), *(float*) (tmp + total+sizeof(float)), *(float*) (tmp + total + 2*sizeof(float)));
	Entity rtn(m_pos_new, m_dir_new);
	rtn.m_id = *(int *) tmp + 1;
	return rtn;
}

Entity::~Entity(){
	if(m_ref)
		delete m_ref;
}