/**
 * \file EnvireMarsPlugins.cpp
 * \author Malte Langosz
 *
 */

#include "EnvireMarsPlugins.hpp"
#include <envire_core/graph/EnvireGraph.hpp>
#include <envire_core/graph/TreeView.hpp>

#include <mars_utils/mathUtils.h>
#include <mars_utils/misc.h>

#include <mars_interfaces/Logging.hpp>
#include <mars_interfaces/sim/ItemPlugin.hpp>

namespace mars
{
    namespace envire_mars_plugins
    {
        using namespace interfaces;

        EnvireMarsPlugins::EnvireMarsPlugins(lib_manager::LibManager *theManager) :
            lib_manager::LibInterface{theManager}
        {
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Heightfield>>::subscribe(ControlCenter::envireGraph.get());
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Plane>>::subscribe(ControlCenter::envireGraph.get());
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Box>>::subscribe(ControlCenter::envireGraph.get());
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Capsule>>::subscribe(ControlCenter::envireGraph.get());
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Cylinder>>::subscribe(ControlCenter::envireGraph.get());
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Mesh>>::subscribe(ControlCenter::envireGraph.get());
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Sphere>>::subscribe(ControlCenter::envireGraph.get());
            // TODO: extend to other types such as motors, sensors, joints
        }

        EnvireMarsPlugins::~EnvireMarsPlugins()
        {
            // unsubscribe from envire graph
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Heightfield>>::unsubscribe();
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Plane>>::unsubscribe();
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Box>>::unsubscribe();
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Capsule>>::unsubscribe();
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Cylinder>>::unsubscribe();
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Mesh>>::unsubscribe();
            GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Sphere>>::unsubscribe();
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Heightfield>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Plane>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Box>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Capsule>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Cylinder>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Mesh>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Sphere>>& e)
        {
            auto& geom = e.item->getData();
            auto config = geom.getFullConfigMap();

            handleConfig(config, e.frame);
        }

        void EnvireMarsPlugins::handleConfig(configmaps::ConfigMap &config, const envire::core::FrameId &frameId)
        {
            if(config.hasKey("plugins"))
            {
                for(auto pluginConfig: config["plugins"])
                {
                    if(!pluginConfig.hasKey("plugin_lib_name"))
                    {
                        LOG_ERROR("envire_mars_plugins: No \"plugin_lib_name\" given in plugins sections of: %s\n", frameId.c_str());
                        return;
                    }
                    std::string pluginLibName = pluginConfig["plugin_lib_name"];
                    // 1. try to get new instance
                    lib_manager::LibInterface *pluginLib;
                    pluginLib = libManager->getNewInstance(pluginLibName);
                    if(!pluginLib)
                    {
                        // try to load the library
                        libManager->loadLibrary(pluginLibName);
                        pluginLib = libManager->getNewInstance(pluginLibName);
                        if(!pluginLib)
                        {
                            LOG_ERROR("envire_mars_plugins: Unable to load plugin \"%s\" for item \"%s\"\n", pluginLibName.c_str(), frameId.c_str());
                            return;
                        }
                    }                    
                    // 2. call plugin init
                    std::shared_ptr<ItemPlugin> plugin{dynamic_cast<ItemPlugin*>(pluginLib)};
                    if(!plugin)
                    {
                        LOG_ERROR("envire_mars_plugins: Unable to cast ItemPugin from \"%s\" for item \"%s\"\n", pluginLibName.c_str(), frameId.c_str());
                        return;
                    }
                    plugin->initPlugin(ControlCenter::envireGraph,
                                       ControlCenter::graphTreeView,
                                       frameId);
                    // 3. attache instance to graph
                    envire::core::Item<ItemPluginItem>::Ptr pluginItemPtr{new envire::core::Item<ItemPluginItem>{ItemPluginItem(std::move(plugin), plugin->getLibName())}};
                    ControlCenter::envireGraph->addItemToFrame(frameId, pluginItemPtr);
                }
            }
        }
    } // end of namespace envire_mars_plugins

} // end of namespace mars

DESTROY_LIB(mars::envire_mars_plugins::EnvireMarsPlugins);
CREATE_LIB(mars::envire_mars_plugins::EnvireMarsPlugins);
