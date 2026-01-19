/**
 * \file EnvireMarsPlugins.hpp
 * \author Malte Langosz
 * \brief Library to load plugins for specific MARS envire items
 *
 */

#pragma once

#include <lib_manager/LibInterface.hpp>

#include <envire_core/items/Item.hpp>
#include <envire_core/events/GraphEventDispatcher.hpp>
#include <envire_core/events/GraphItemEventDispatcher.hpp>

#include <envire_types/geometry/Heightfield.hpp>
#include <envire_types/geometry/Plane.hpp>
#include <envire_types/geometry/Box.hpp>
#include <envire_types/geometry/Capsule.hpp>
#include <envire_types/geometry/Cylinder.hpp>
#include <envire_types/geometry/Mesh.hpp>
#include <envire_types/geometry/Sphere.hpp>
#include <envire_types/Link.hpp>

namespace mars
{
    namespace envire_mars_plugins
    {
        // move the typedef to separate file
        class EnvireMarsPlugins : public lib_manager::LibInterface,
                                  public envire::core::GraphEventDispatcher,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Heightfield>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Plane>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Box>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Capsule>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Cylinder>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Mesh>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::geometry::Sphere>>,
                                  public envire::core::GraphItemEventDispatcher<envire::core::Item<::envire::types::Link>>

        {

        public:
            EnvireMarsPlugins(lib_manager::LibManager *theManager); ///< Constructor of the \c class Simulator.
            virtual ~EnvireMarsPlugins();

            // --- LibInterface ---
            int getLibVersion() const override
            {
                return 1;
            }

            const std::string getLibName() const override
            {
                return std::string{"envire_mars_plugins"};
            }

            CREATE_MODULE_INFO();

            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Heightfield>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Plane>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Box>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Capsule>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Cylinder>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Mesh>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::geometry::Sphere>>& e) override;
            virtual void itemAdded(const envire::core::TypedItemAddedEvent<envire::core::Item<::envire::types::Link>>& e) override;

        private:
            void handleConfig(configmaps::ConfigMap &config, const envire::core::FrameId &frameId);
        };

    } // end of namespace envire_mars_plugins
} // end of namespace mars
