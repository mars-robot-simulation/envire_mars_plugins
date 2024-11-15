#include <mars_interfaces/sim/ItemPlugin.hpp>
#include <envire_core/plugin/Plugin.hpp>


BOOST_SERIALIZATION_SPLIT_FREE(mars::interfaces::ItemPluginItem)

namespace boost
{
    namespace serialization
    {

        template<class Archive> inline void save(Archive & ar, const mars::interfaces::ItemPluginItem &value, const unsigned int file_version)
        {
            std::string buffer;
            buffer = value.libName;
            ar << buffer;
        }

        template<class Archive> inline void load(Archive & ar, mars::interfaces::ItemPluginItem &value, const unsigned int file_version)
        {
            std::string buffer;
            ar >> buffer;
            value.libName = buffer;
        }

    }
}

ENVIRE_REGISTER_ITEM(mars::interfaces::ItemPluginItem)
