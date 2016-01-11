//
// Created by achille on 10/01/16.
//

#ifndef FODUS_ELEMENTLIST_H
#define FODUS_ELEMENTLIST_H

#include "ElementList.hpp"
#include "Case.hpp"
#include "Perso.hpp"
// User defined class template specialization
namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {


            template<>
            struct convert<state::ElementList> {
                msgpack::object const& operator()(msgpack::object const& o, state::ElementList& v) const {
                    if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
                    // if (o.via.array.size != 2) throw msgpack::type_error();
                    v = state::ElementList();
                    int size = o.via.array.size;
                    for(int i = 0; i < size; i++)
                    {
                        state::Element* ptr;
                        try{
                            // trying to convert to case
                            ptr = new state::Case(o.via.array.ptr[i].as<state::Case>());
                        }catch (const std::exception& e){
                            // cast to Perso
                            ptr = new state::Perso(o.via.array.ptr[i].as<state::Perso>());
                        }
                    v.push_back(ptr);
                    }

                    return o;
                }
            };

            template<>
            struct pack<state::ElementList> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, state::ElementList const& v) const {
                    // packing member variables as an array.
                    o.pack_array((int)v.size());
                    for(auto& el:v){
                        if(el->type == Mobile){
                            std::unique_ptr<state::Perso> ptr;
                            ptr.reset( (state::Perso*) el->clone());
                            o.pack(ptr);
                        }
                        else
                        {
                            std::unique_ptr<state::Case> ptr;
                            ptr.reset( (state::Case*) el->clone());
                            o.pack(ptr);
                        }
                    }
                    return o;
                }
            };

            template <>
            struct object_with_zone<state::ElementList> {
                void operator()(msgpack::object::with_zone& o, state::ElementList const& v) const {
                    o.type = type::ARRAY;
                    o.via.array.size = 2;
                    o.via.array.ptr = static_cast<msgpack::object*>(
                            o.zone.allocate_align(sizeof(msgpack::object) * o.via.array.size));

                }
            };


        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack


#endif //FODUS_ELEMENTLIST_H
