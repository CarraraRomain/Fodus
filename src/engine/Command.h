//
// Created by achille on 10/01/16.
//

#ifndef FODUS_COMMAND_H
#define FODUS_COMMAND_H

#include "Command.hpp"
#include "MoveCommand.hpp"
#include "SkillCommand.hpp"
// User defined class template specialization
namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {


            template<>
            struct convert<engine::Command*> {
                msgpack::object const& operator()(msgpack::object const& o, engine::Command*& v) const {
                    if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
                    std::cout << "Convert ptr com";
                        try{
                            // trying to convert to MoveCommand
                            v =  new engine::MoveCommand(o.via.array.ptr[0].as<engine::MoveCommand>());
                        }catch (const std::exception& e){
                            // cast to SkillCommand
                            v = new engine::SkillCommand(o.via.array.ptr[0].as<engine::SkillCommand>());
                        }


                    return o;
                }
            };
            template<>
            struct convert<engine::Command> {
                msgpack::object const& operator()(msgpack::object const& o, engine::Command& v) const {
                    if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
                    std::cout << "Convert com";
                        try{
                            // trying to convert to MoveCommand
                            v =  engine::MoveCommand(o.via.array.ptr[0].as<engine::MoveCommand>());
                        }catch (const std::exception& e){
                            // cast to SkillCommand
                            v = engine::SkillCommand(o.via.array.ptr[0].as<engine::SkillCommand>());
                        }


                    return o;
                }
            };

            template<>
            struct pack<engine::Command*> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, engine::Command* const& v) const {
                    std::cout << "Packing ptr";
                        if(v->type == Move ){
                            std::cout << "Packing ptr move";
                            o.pack_array(6);
                            engine::MoveCommand com = *(engine::MoveCommand*) v;
                            o.pack(com);
                        }
                        else if (v->type == Skill)
                        {
                            std::cout << "Packing ptr skill";
                            o.pack_array(6);
                            engine::SkillCommand com = *(engine::SkillCommand*) v;
                            o.pack(com);
                        }

                    return o;
                }
            };
            template<>
            struct pack<engine::Command> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, engine::Command const& v) const {
                    std::cout << "Packing com";
                        if(v.type == Move ){
                            o.pack_array((int)6);
                            engine::MoveCommand com = (const engine::MoveCommand&) v;
                            o.pack(com);
                        }
                        else if (v.type == Skill)
                        {
                            o.pack_array((int) 6);
                            engine::SkillCommand com = (const engine::SkillCommand&) v;
                            o.pack(com);
                        }

                    return o;
                }
            };




        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack


#endif //FODUS_ELEMENTLIST_H
