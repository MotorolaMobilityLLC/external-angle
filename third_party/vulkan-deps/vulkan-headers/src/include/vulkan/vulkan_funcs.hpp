// Copyright 2015-2022 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
//

// This header is generated from the Khronos Vulkan XML API Registry.

#ifndef VULKAN_FUNCS_HPP
#  define VULKAN_FUNCS_HPP

namespace VULKAN_HPP_NAMESPACE
{

  //===========================
  //=== COMMAND Definitions ===
  //===========================


  //=== VK_VERSION_1_0 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result createInstance( const VULKAN_HPP_NAMESPACE::InstanceCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Instance * pInstance, Dispatch const & d  ) VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateInstance( reinterpret_cast<const VkInstanceCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkInstance *>( pInstance ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Instance >::type createInstance( const VULKAN_HPP_NAMESPACE::InstanceCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Instance  instance;
    Result result = static_cast<Result>( d.vkCreateInstance( reinterpret_cast<const VkInstanceCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkInstance *>( &instance ) ) );
    return createResultValue( result, instance, VULKAN_HPP_NAMESPACE_STRING "::createInstance" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Instance, Dispatch>>::type createInstanceUnique( const VULKAN_HPP_NAMESPACE::InstanceCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Instance instance;
    Result result = static_cast<Result>( d.vkCreateInstance( reinterpret_cast<const VkInstanceCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkInstance *>( &instance ) ) );
    ObjectDestroy<NoParent, Dispatch> deleter( allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Instance, Dispatch>( result, instance, VULKAN_HPP_NAMESPACE_STRING "::createInstanceUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyInstance( m_instance, reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyInstance( m_instance, reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::enumeratePhysicalDevices( uint32_t * pPhysicalDeviceCount, VULKAN_HPP_NAMESPACE::PhysicalDevice * pPhysicalDevices, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumeratePhysicalDevices( m_instance, pPhysicalDeviceCount, reinterpret_cast<VkPhysicalDevice *>( pPhysicalDevices ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PhysicalDeviceAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDevice, PhysicalDeviceAllocator>>::type Instance::enumeratePhysicalDevices( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDevice, PhysicalDeviceAllocator> physicalDevices;
    uint32_t physicalDeviceCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDevices( m_instance, &physicalDeviceCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && physicalDeviceCount )
      {
        physicalDevices.resize( physicalDeviceCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDevices( m_instance, &physicalDeviceCount, reinterpret_cast<VkPhysicalDevice *>( physicalDevices.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( physicalDeviceCount <= physicalDevices.size() );
      if ( physicalDeviceCount < physicalDevices.size() )
      {
        physicalDevices.resize( physicalDeviceCount );
      }
    }
    return createResultValue( result, physicalDevices, VULKAN_HPP_NAMESPACE_STRING"::Instance::enumeratePhysicalDevices" );
  }

  template <typename PhysicalDeviceAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PhysicalDevice>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDevice, PhysicalDeviceAllocator>>::type Instance::enumeratePhysicalDevices( PhysicalDeviceAllocator & physicalDeviceAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDevice, PhysicalDeviceAllocator> physicalDevices( physicalDeviceAllocator );
    uint32_t physicalDeviceCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDevices( m_instance, &physicalDeviceCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && physicalDeviceCount )
      {
        physicalDevices.resize( physicalDeviceCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDevices( m_instance, &physicalDeviceCount, reinterpret_cast<VkPhysicalDevice *>( physicalDevices.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( physicalDeviceCount <= physicalDevices.size() );
      if ( physicalDeviceCount < physicalDevices.size() )
      {
        physicalDevices.resize( physicalDeviceCount );
      }
    }
    return createResultValue( result, physicalDevices, VULKAN_HPP_NAMESPACE_STRING"::Instance::enumeratePhysicalDevices" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getFeatures( VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures * pFeatures, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceFeatures( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures *>( pFeatures ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures  PhysicalDevice::getFeatures( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures  features;
    d.vkGetPhysicalDeviceFeatures( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures *>( &features ) );
    return features;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getFormatProperties( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::FormatProperties * pFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties *>( pFormatProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::FormatProperties  PhysicalDevice::getFormatProperties( VULKAN_HPP_NAMESPACE::Format format, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::FormatProperties  formatProperties;
    d.vkGetPhysicalDeviceFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties *>( &formatProperties ) );
    return formatProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getImageFormatProperties( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::ImageTiling tiling, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageCreateFlags flags, VULKAN_HPP_NAMESPACE::ImageFormatProperties * pImageFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkImageTiling>( tiling ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageCreateFlags>( flags ), reinterpret_cast<VkImageFormatProperties *>( pImageFormatProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ImageFormatProperties >::type PhysicalDevice::getImageFormatProperties( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::ImageTiling tiling, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageCreateFlags flags, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ImageFormatProperties  imageFormatProperties;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkImageTiling>( tiling ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageCreateFlags>( flags ), reinterpret_cast<VkImageFormatProperties *>( &imageFormatProperties ) ) );
    return createResultValue( result, imageFormatProperties, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getImageFormatProperties" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getProperties( VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceProperties( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties *>( pProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties  PhysicalDevice::getProperties( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties  properties;
    d.vkGetPhysicalDeviceProperties( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties *>( &properties ) );
    return properties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getQueueFamilyProperties( uint32_t * pQueueFamilyPropertyCount, VULKAN_HPP_NAMESPACE::QueueFamilyProperties * pQueueFamilyProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceQueueFamilyProperties( m_physicalDevice, pQueueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties *>( pQueueFamilyProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename QueueFamilyPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<QueueFamilyProperties, QueueFamilyPropertiesAllocator> PhysicalDevice::getQueueFamilyProperties( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<QueueFamilyProperties, QueueFamilyPropertiesAllocator> queueFamilyProperties;
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    queueFamilyProperties.resize( queueFamilyPropertyCount );
    d.vkGetPhysicalDeviceQueueFamilyProperties( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    return queueFamilyProperties;
  }

  template <typename QueueFamilyPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, QueueFamilyProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<QueueFamilyProperties, QueueFamilyPropertiesAllocator> PhysicalDevice::getQueueFamilyProperties( QueueFamilyPropertiesAllocator & queueFamilyPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<QueueFamilyProperties, QueueFamilyPropertiesAllocator> queueFamilyProperties( queueFamilyPropertiesAllocator );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    queueFamilyProperties.resize( queueFamilyPropertyCount );
    d.vkGetPhysicalDeviceQueueFamilyProperties( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    return queueFamilyProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getMemoryProperties( VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties * pMemoryProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceMemoryProperties( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties *>( pMemoryProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties  PhysicalDevice::getMemoryProperties( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties  memoryProperties;
    d.vkGetPhysicalDeviceMemoryProperties( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties *>( &memoryProperties ) );
    return memoryProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE PFN_vkVoidFunction Instance::getProcAddr( const char * pName, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetInstanceProcAddr( m_instance, pName );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE PFN_vkVoidFunction Instance::getProcAddr( const std::string & name, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetInstanceProcAddr( m_instance, name.c_str() );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE PFN_vkVoidFunction Device::getProcAddr( const char * pName, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetDeviceProcAddr( m_device, pName );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE PFN_vkVoidFunction Device::getProcAddr( const std::string & name, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetDeviceProcAddr( m_device, name.c_str() );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::createDevice( const VULKAN_HPP_NAMESPACE::DeviceCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Device * pDevice, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDevice( m_physicalDevice, reinterpret_cast<const VkDeviceCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDevice *>( pDevice ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Device >::type PhysicalDevice::createDevice( const VULKAN_HPP_NAMESPACE::DeviceCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Device  device;
    Result result = static_cast<Result>( d.vkCreateDevice( m_physicalDevice, reinterpret_cast<const VkDeviceCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDevice *>( &device ) ) );
    return createResultValue( result, device, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::createDevice" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Device, Dispatch>>::type PhysicalDevice::createDeviceUnique( const VULKAN_HPP_NAMESPACE::DeviceCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Device device;
    Result result = static_cast<Result>( d.vkCreateDevice( m_physicalDevice, reinterpret_cast<const VkDeviceCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDevice *>( &device ) ) );
    ObjectDestroy<NoParent, Dispatch> deleter( allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Device, Dispatch>( result, device, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::createDeviceUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDevice( m_device, reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDevice( m_device, reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result enumerateInstanceExtensionProperties( const char * pLayerName, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::ExtensionProperties * pProperties, Dispatch const & d  ) VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumerateInstanceExtensionProperties( pLayerName, pPropertyCount, reinterpret_cast<VkExtensionProperties *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename ExtensionPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<ExtensionProperties, ExtensionPropertiesAllocator>>::type enumerateInstanceExtensionProperties( Optional<const std::string> layerName, Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<ExtensionProperties, ExtensionPropertiesAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateInstanceExtensionProperties( layerName ? layerName->c_str() : nullptr, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateInstanceExtensionProperties( layerName ? layerName->c_str() : nullptr, &propertyCount, reinterpret_cast<VkExtensionProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::enumerateInstanceExtensionProperties" );
  }

  template <typename ExtensionPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, ExtensionProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<ExtensionProperties, ExtensionPropertiesAllocator>>::type enumerateInstanceExtensionProperties( Optional<const std::string> layerName, ExtensionPropertiesAllocator & extensionPropertiesAllocator, Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<ExtensionProperties, ExtensionPropertiesAllocator> properties( extensionPropertiesAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateInstanceExtensionProperties( layerName ? layerName->c_str() : nullptr, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateInstanceExtensionProperties( layerName ? layerName->c_str() : nullptr, &propertyCount, reinterpret_cast<VkExtensionProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::enumerateInstanceExtensionProperties" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::enumerateDeviceExtensionProperties( const char * pLayerName, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::ExtensionProperties * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumerateDeviceExtensionProperties( m_physicalDevice, pLayerName, pPropertyCount, reinterpret_cast<VkExtensionProperties *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename ExtensionPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<ExtensionProperties, ExtensionPropertiesAllocator>>::type PhysicalDevice::enumerateDeviceExtensionProperties( Optional<const std::string> layerName, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<ExtensionProperties, ExtensionPropertiesAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateDeviceExtensionProperties( m_physicalDevice, layerName ? layerName->c_str() : nullptr, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateDeviceExtensionProperties( m_physicalDevice, layerName ? layerName->c_str() : nullptr, &propertyCount, reinterpret_cast<VkExtensionProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::enumerateDeviceExtensionProperties" );
  }

  template <typename ExtensionPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, ExtensionProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<ExtensionProperties, ExtensionPropertiesAllocator>>::type PhysicalDevice::enumerateDeviceExtensionProperties( Optional<const std::string> layerName, ExtensionPropertiesAllocator & extensionPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<ExtensionProperties, ExtensionPropertiesAllocator> properties( extensionPropertiesAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateDeviceExtensionProperties( m_physicalDevice, layerName ? layerName->c_str() : nullptr, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateDeviceExtensionProperties( m_physicalDevice, layerName ? layerName->c_str() : nullptr, &propertyCount, reinterpret_cast<VkExtensionProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::enumerateDeviceExtensionProperties" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result enumerateInstanceLayerProperties( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::LayerProperties * pProperties, Dispatch const & d  ) VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumerateInstanceLayerProperties( pPropertyCount, reinterpret_cast<VkLayerProperties *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename LayerPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<LayerProperties, LayerPropertiesAllocator>>::type enumerateInstanceLayerProperties( Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<LayerProperties, LayerPropertiesAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateInstanceLayerProperties( &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateInstanceLayerProperties( &propertyCount, reinterpret_cast<VkLayerProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::enumerateInstanceLayerProperties" );
  }

  template <typename LayerPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, LayerProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<LayerProperties, LayerPropertiesAllocator>>::type enumerateInstanceLayerProperties( LayerPropertiesAllocator & layerPropertiesAllocator, Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<LayerProperties, LayerPropertiesAllocator> properties( layerPropertiesAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateInstanceLayerProperties( &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateInstanceLayerProperties( &propertyCount, reinterpret_cast<VkLayerProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::enumerateInstanceLayerProperties" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::enumerateDeviceLayerProperties( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::LayerProperties * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumerateDeviceLayerProperties( m_physicalDevice, pPropertyCount, reinterpret_cast<VkLayerProperties *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename LayerPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<LayerProperties, LayerPropertiesAllocator>>::type PhysicalDevice::enumerateDeviceLayerProperties( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<LayerProperties, LayerPropertiesAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateDeviceLayerProperties( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateDeviceLayerProperties( m_physicalDevice, &propertyCount, reinterpret_cast<VkLayerProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::enumerateDeviceLayerProperties" );
  }

  template <typename LayerPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, LayerProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<LayerProperties, LayerPropertiesAllocator>>::type PhysicalDevice::enumerateDeviceLayerProperties( LayerPropertiesAllocator & layerPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<LayerProperties, LayerPropertiesAllocator> properties( layerPropertiesAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumerateDeviceLayerProperties( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkEnumerateDeviceLayerProperties( m_physicalDevice, &propertyCount, reinterpret_cast<VkLayerProperties *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::enumerateDeviceLayerProperties" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getQueue( uint32_t queueFamilyIndex, uint32_t queueIndex, VULKAN_HPP_NAMESPACE::Queue * pQueue, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceQueue( m_device, queueFamilyIndex, queueIndex, reinterpret_cast<VkQueue *>( pQueue ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::Queue  Device::getQueue( uint32_t queueFamilyIndex, uint32_t queueIndex, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Queue  queue;
    d.vkGetDeviceQueue( m_device, queueFamilyIndex, queueIndex, reinterpret_cast<VkQueue *>( &queue ) );
    return queue;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::submit( uint32_t submitCount, const VULKAN_HPP_NAMESPACE::SubmitInfo * pSubmits, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueueSubmit( m_queue, submitCount, reinterpret_cast<const VkSubmitInfo *>( pSubmits ), static_cast<VkFence>( fence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Queue::submit( ArrayProxy<const VULKAN_HPP_NAMESPACE::SubmitInfo> const & submits, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueueSubmit( m_queue, submits.size(), reinterpret_cast<const VkSubmitInfo *>( submits.data() ), static_cast<VkFence>( fence ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::submit" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::waitIdle( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueueWaitIdle( m_queue ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Queue::waitIdle( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueueWaitIdle( m_queue ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::waitIdle" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitIdle( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkDeviceWaitIdle( m_device ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::waitIdle( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkDeviceWaitIdle( m_device ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::waitIdle" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::allocateMemory( const VULKAN_HPP_NAMESPACE::MemoryAllocateInfo * pAllocateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DeviceMemory * pMemory, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAllocateMemory( m_device, reinterpret_cast<const VkMemoryAllocateInfo *>( pAllocateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDeviceMemory *>( pMemory ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DeviceMemory >::type Device::allocateMemory( const VULKAN_HPP_NAMESPACE::MemoryAllocateInfo & allocateInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DeviceMemory  memory;
    Result result = static_cast<Result>( d.vkAllocateMemory( m_device, reinterpret_cast<const VkMemoryAllocateInfo *>( &allocateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDeviceMemory *>( &memory ) ) );
    return createResultValue( result, memory, VULKAN_HPP_NAMESPACE_STRING "::Device::allocateMemory" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DeviceMemory, Dispatch>>::type Device::allocateMemoryUnique( const VULKAN_HPP_NAMESPACE::MemoryAllocateInfo & allocateInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DeviceMemory memory;
    Result result = static_cast<Result>( d.vkAllocateMemory( m_device, reinterpret_cast<const VkMemoryAllocateInfo *>( &allocateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDeviceMemory *>( &memory ) ) );
    ObjectFree<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DeviceMemory, Dispatch>( result, memory, VULKAN_HPP_NAMESPACE_STRING "::Device::allocateMemoryUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::freeMemory( VULKAN_HPP_NAMESPACE::DeviceMemory memory, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkFreeMemory( m_device, static_cast<VkDeviceMemory>( memory ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::freeMemory( VULKAN_HPP_NAMESPACE::DeviceMemory memory, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkFreeMemory( m_device, static_cast<VkDeviceMemory>( memory ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void ( Device::free )( VULKAN_HPP_NAMESPACE::DeviceMemory memory, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkFreeMemory( m_device, static_cast<VkDeviceMemory>( memory ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void ( Device::free )( VULKAN_HPP_NAMESPACE::DeviceMemory memory, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkFreeMemory( m_device, static_cast<VkDeviceMemory>( memory ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::mapMemory( VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::DeviceSize size, VULKAN_HPP_NAMESPACE::MemoryMapFlags flags, void ** ppData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkMapMemory( m_device, static_cast<VkDeviceMemory>( memory ), static_cast<VkDeviceSize>( offset ), static_cast<VkDeviceSize>( size ), static_cast<VkMemoryMapFlags>( flags ), ppData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void *>::type Device::mapMemory( VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::DeviceSize size, VULKAN_HPP_NAMESPACE::MemoryMapFlags flags, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    void * pData;
    Result result = static_cast<Result>( d.vkMapMemory( m_device, static_cast<VkDeviceMemory>( memory ), static_cast<VkDeviceSize>( offset ), static_cast<VkDeviceSize>( size ), static_cast<VkMemoryMapFlags>( flags ), &pData ) );
    return createResultValue( result, pData, VULKAN_HPP_NAMESPACE_STRING "::Device::mapMemory" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::unmapMemory( VULKAN_HPP_NAMESPACE::DeviceMemory memory, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkUnmapMemory( m_device, static_cast<VkDeviceMemory>( memory ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::flushMappedMemoryRanges( uint32_t memoryRangeCount, const VULKAN_HPP_NAMESPACE::MappedMemoryRange * pMemoryRanges, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkFlushMappedMemoryRanges( m_device, memoryRangeCount, reinterpret_cast<const VkMappedMemoryRange *>( pMemoryRanges ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::flushMappedMemoryRanges( ArrayProxy<const VULKAN_HPP_NAMESPACE::MappedMemoryRange> const & memoryRanges, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkFlushMappedMemoryRanges( m_device, memoryRanges.size(), reinterpret_cast<const VkMappedMemoryRange *>( memoryRanges.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::flushMappedMemoryRanges" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::invalidateMappedMemoryRanges( uint32_t memoryRangeCount, const VULKAN_HPP_NAMESPACE::MappedMemoryRange * pMemoryRanges, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkInvalidateMappedMemoryRanges( m_device, memoryRangeCount, reinterpret_cast<const VkMappedMemoryRange *>( pMemoryRanges ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::invalidateMappedMemoryRanges( ArrayProxy<const VULKAN_HPP_NAMESPACE::MappedMemoryRange> const & memoryRanges, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkInvalidateMappedMemoryRanges( m_device, memoryRanges.size(), reinterpret_cast<const VkMappedMemoryRange *>( memoryRanges.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::invalidateMappedMemoryRanges" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getMemoryCommitment( VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize * pCommittedMemoryInBytes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceMemoryCommitment( m_device, static_cast<VkDeviceMemory>( memory ), reinterpret_cast<VkDeviceSize *>( pCommittedMemoryInBytes ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::DeviceSize  Device::getMemoryCommitment( VULKAN_HPP_NAMESPACE::DeviceMemory memory, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DeviceSize  committedMemoryInBytes;
    d.vkGetDeviceMemoryCommitment( m_device, static_cast<VkDeviceMemory>( memory ), reinterpret_cast<VkDeviceSize *>( &committedMemoryInBytes ) );
    return committedMemoryInBytes;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindBufferMemory( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize memoryOffset, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindBufferMemory( m_device, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceMemory>( memory ), static_cast<VkDeviceSize>( memoryOffset ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindBufferMemory( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize memoryOffset, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindBufferMemory( m_device, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceMemory>( memory ), static_cast<VkDeviceSize>( memoryOffset ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindBufferMemory" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindImageMemory( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize memoryOffset, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindImageMemory( m_device, static_cast<VkImage>( image ), static_cast<VkDeviceMemory>( memory ), static_cast<VkDeviceSize>( memoryOffset ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindImageMemory( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::DeviceSize memoryOffset, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindImageMemory( m_device, static_cast<VkImage>( image ), static_cast<VkDeviceMemory>( memory ), static_cast<VkDeviceSize>( memoryOffset ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindImageMemory" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getBufferMemoryRequirements( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::MemoryRequirements * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetBufferMemoryRequirements( m_device, static_cast<VkBuffer>( buffer ), reinterpret_cast<VkMemoryRequirements *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements  Device::getBufferMemoryRequirements( VULKAN_HPP_NAMESPACE::Buffer buffer, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements  memoryRequirements;
    d.vkGetBufferMemoryRequirements( m_device, static_cast<VkBuffer>( buffer ), reinterpret_cast<VkMemoryRequirements *>( &memoryRequirements ) );
    return memoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageMemoryRequirements( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::MemoryRequirements * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageMemoryRequirements( m_device, static_cast<VkImage>( image ), reinterpret_cast<VkMemoryRequirements *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements  Device::getImageMemoryRequirements( VULKAN_HPP_NAMESPACE::Image image, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements  memoryRequirements;
    d.vkGetImageMemoryRequirements( m_device, static_cast<VkImage>( image ), reinterpret_cast<VkMemoryRequirements *>( &memoryRequirements ) );
    return memoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageSparseMemoryRequirements( VULKAN_HPP_NAMESPACE::Image image, uint32_t * pSparseMemoryRequirementCount, VULKAN_HPP_NAMESPACE::SparseImageMemoryRequirements * pSparseMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageSparseMemoryRequirements( m_device, static_cast<VkImage>( image ), pSparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements *>( pSparseMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageMemoryRequirementsAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements, SparseImageMemoryRequirementsAllocator> Device::getImageSparseMemoryRequirements( VULKAN_HPP_NAMESPACE::Image image, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements, SparseImageMemoryRequirementsAllocator> sparseMemoryRequirements;
    uint32_t sparseMemoryRequirementCount;
    d.vkGetImageSparseMemoryRequirements( m_device, static_cast<VkImage>( image ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetImageSparseMemoryRequirements( m_device, static_cast<VkImage>( image ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }

  template <typename SparseImageMemoryRequirementsAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageMemoryRequirements>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements, SparseImageMemoryRequirementsAllocator> Device::getImageSparseMemoryRequirements( VULKAN_HPP_NAMESPACE::Image image, SparseImageMemoryRequirementsAllocator & sparseImageMemoryRequirementsAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements, SparseImageMemoryRequirementsAllocator> sparseMemoryRequirements( sparseImageMemoryRequirementsAllocator );
    uint32_t sparseMemoryRequirementCount;
    d.vkGetImageSparseMemoryRequirements( m_device, static_cast<VkImage>( image ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetImageSparseMemoryRequirements( m_device, static_cast<VkImage>( image ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getSparseImageFormatProperties( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::SampleCountFlagBits samples, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageTiling tiling, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::SparseImageFormatProperties * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceSparseImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkSampleCountFlagBits>( samples ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageTiling>( tiling ), pPropertyCount, reinterpret_cast<VkSparseImageFormatProperties *>( pProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageFormatPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageFormatProperties, SparseImageFormatPropertiesAllocator> PhysicalDevice::getSparseImageFormatProperties( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::SampleCountFlagBits samples, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageTiling tiling, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageFormatProperties, SparseImageFormatPropertiesAllocator> properties;
    uint32_t propertyCount;
    d.vkGetPhysicalDeviceSparseImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkSampleCountFlagBits>( samples ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageTiling>( tiling ), &propertyCount, nullptr );
    properties.resize( propertyCount );
    d.vkGetPhysicalDeviceSparseImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkSampleCountFlagBits>( samples ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageTiling>( tiling ), &propertyCount, reinterpret_cast<VkSparseImageFormatProperties *>( properties.data() ) );
    VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
    return properties;
  }

  template <typename SparseImageFormatPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageFormatProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageFormatProperties, SparseImageFormatPropertiesAllocator> PhysicalDevice::getSparseImageFormatProperties( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::SampleCountFlagBits samples, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageTiling tiling, SparseImageFormatPropertiesAllocator & sparseImageFormatPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageFormatProperties, SparseImageFormatPropertiesAllocator> properties( sparseImageFormatPropertiesAllocator );
    uint32_t propertyCount;
    d.vkGetPhysicalDeviceSparseImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkSampleCountFlagBits>( samples ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageTiling>( tiling ), &propertyCount, nullptr );
    properties.resize( propertyCount );
    d.vkGetPhysicalDeviceSparseImageFormatProperties( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkSampleCountFlagBits>( samples ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageTiling>( tiling ), &propertyCount, reinterpret_cast<VkSparseImageFormatProperties *>( properties.data() ) );
    VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
    return properties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::bindSparse( uint32_t bindInfoCount, const VULKAN_HPP_NAMESPACE::BindSparseInfo * pBindInfo, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueueBindSparse( m_queue, bindInfoCount, reinterpret_cast<const VkBindSparseInfo *>( pBindInfo ), static_cast<VkFence>( fence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Queue::bindSparse( ArrayProxy<const VULKAN_HPP_NAMESPACE::BindSparseInfo> const & bindInfo, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueueBindSparse( m_queue, bindInfo.size(), reinterpret_cast<const VkBindSparseInfo *>( bindInfo.data() ), static_cast<VkFence>( fence ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::bindSparse" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createFence( const VULKAN_HPP_NAMESPACE::FenceCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Fence * pFence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateFence( m_device, reinterpret_cast<const VkFenceCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkFence *>( pFence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Fence >::type Device::createFence( const VULKAN_HPP_NAMESPACE::FenceCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Fence  fence;
    Result result = static_cast<Result>( d.vkCreateFence( m_device, reinterpret_cast<const VkFenceCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFence *>( &fence ) ) );
    return createResultValue( result, fence, VULKAN_HPP_NAMESPACE_STRING "::Device::createFence" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Fence, Dispatch>>::type Device::createFenceUnique( const VULKAN_HPP_NAMESPACE::FenceCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Fence fence;
    Result result = static_cast<Result>( d.vkCreateFence( m_device, reinterpret_cast<const VkFenceCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFence *>( &fence ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Fence, Dispatch>( result, fence, VULKAN_HPP_NAMESPACE_STRING "::Device::createFenceUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyFence( VULKAN_HPP_NAMESPACE::Fence fence, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyFence( m_device, static_cast<VkFence>( fence ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyFence( VULKAN_HPP_NAMESPACE::Fence fence, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyFence( m_device, static_cast<VkFence>( fence ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Fence fence, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyFence( m_device, static_cast<VkFence>( fence ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Fence fence, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyFence( m_device, static_cast<VkFence>( fence ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::resetFences( uint32_t fenceCount, const VULKAN_HPP_NAMESPACE::Fence * pFences, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkResetFences( m_device, fenceCount, reinterpret_cast<const VkFence *>( pFences ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::resetFences( ArrayProxy<const VULKAN_HPP_NAMESPACE::Fence> const & fences, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkResetFences( m_device, fences.size(), reinterpret_cast<const VkFence *>( fences.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::resetFences" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getFenceStatus( VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetFenceStatus( m_device, static_cast<VkFence>( fence ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getFenceStatus( VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkGetFenceStatus( m_device, static_cast<VkFence>( fence ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::getFenceStatus", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eNotReady } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitForFences( uint32_t fenceCount, const VULKAN_HPP_NAMESPACE::Fence * pFences, VULKAN_HPP_NAMESPACE::Bool32 waitAll, uint64_t timeout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkWaitForFences( m_device, fenceCount, reinterpret_cast<const VkFence *>( pFences ), static_cast<VkBool32>( waitAll ), timeout ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitForFences( ArrayProxy<const VULKAN_HPP_NAMESPACE::Fence> const & fences, VULKAN_HPP_NAMESPACE::Bool32 waitAll, uint64_t timeout, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkWaitForFences( m_device, fences.size(), reinterpret_cast<const VkFence *>( fences.data() ), static_cast<VkBool32>( waitAll ), timeout ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::waitForFences", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eTimeout } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createSemaphore( const VULKAN_HPP_NAMESPACE::SemaphoreCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Semaphore * pSemaphore, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateSemaphore( m_device, reinterpret_cast<const VkSemaphoreCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSemaphore *>( pSemaphore ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Semaphore >::type Device::createSemaphore( const VULKAN_HPP_NAMESPACE::SemaphoreCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Semaphore  semaphore;
    Result result = static_cast<Result>( d.vkCreateSemaphore( m_device, reinterpret_cast<const VkSemaphoreCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSemaphore *>( &semaphore ) ) );
    return createResultValue( result, semaphore, VULKAN_HPP_NAMESPACE_STRING "::Device::createSemaphore" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Semaphore, Dispatch>>::type Device::createSemaphoreUnique( const VULKAN_HPP_NAMESPACE::SemaphoreCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Semaphore semaphore;
    Result result = static_cast<Result>( d.vkCreateSemaphore( m_device, reinterpret_cast<const VkSemaphoreCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSemaphore *>( &semaphore ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Semaphore, Dispatch>( result, semaphore, VULKAN_HPP_NAMESPACE_STRING "::Device::createSemaphoreUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySemaphore( VULKAN_HPP_NAMESPACE::Semaphore semaphore, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySemaphore( m_device, static_cast<VkSemaphore>( semaphore ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySemaphore( VULKAN_HPP_NAMESPACE::Semaphore semaphore, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySemaphore( m_device, static_cast<VkSemaphore>( semaphore ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Semaphore semaphore, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySemaphore( m_device, static_cast<VkSemaphore>( semaphore ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Semaphore semaphore, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySemaphore( m_device, static_cast<VkSemaphore>( semaphore ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createEvent( const VULKAN_HPP_NAMESPACE::EventCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Event * pEvent, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateEvent( m_device, reinterpret_cast<const VkEventCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkEvent *>( pEvent ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Event >::type Device::createEvent( const VULKAN_HPP_NAMESPACE::EventCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Event  event;
    Result result = static_cast<Result>( d.vkCreateEvent( m_device, reinterpret_cast<const VkEventCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkEvent *>( &event ) ) );
    return createResultValue( result, event, VULKAN_HPP_NAMESPACE_STRING "::Device::createEvent" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Event, Dispatch>>::type Device::createEventUnique( const VULKAN_HPP_NAMESPACE::EventCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Event event;
    Result result = static_cast<Result>( d.vkCreateEvent( m_device, reinterpret_cast<const VkEventCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkEvent *>( &event ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Event, Dispatch>( result, event, VULKAN_HPP_NAMESPACE_STRING "::Device::createEventUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyEvent( VULKAN_HPP_NAMESPACE::Event event, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyEvent( m_device, static_cast<VkEvent>( event ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyEvent( VULKAN_HPP_NAMESPACE::Event event, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyEvent( m_device, static_cast<VkEvent>( event ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Event event, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyEvent( m_device, static_cast<VkEvent>( event ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Event event, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyEvent( m_device, static_cast<VkEvent>( event ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getEventStatus( VULKAN_HPP_NAMESPACE::Event event, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetEventStatus( m_device, static_cast<VkEvent>( event ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getEventStatus( VULKAN_HPP_NAMESPACE::Event event, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkGetEventStatus( m_device, static_cast<VkEvent>( event ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::getEventStatus", { VULKAN_HPP_NAMESPACE::Result::eEventSet, VULKAN_HPP_NAMESPACE::Result::eEventReset } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setEvent( VULKAN_HPP_NAMESPACE::Event event, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetEvent( m_device, static_cast<VkEvent>( event ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setEvent( VULKAN_HPP_NAMESPACE::Event event, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetEvent( m_device, static_cast<VkEvent>( event ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setEvent" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::resetEvent( VULKAN_HPP_NAMESPACE::Event event, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkResetEvent( m_device, static_cast<VkEvent>( event ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::resetEvent( VULKAN_HPP_NAMESPACE::Event event, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkResetEvent( m_device, static_cast<VkEvent>( event ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::resetEvent" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createQueryPool( const VULKAN_HPP_NAMESPACE::QueryPoolCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::QueryPool * pQueryPool, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateQueryPool( m_device, reinterpret_cast<const VkQueryPoolCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkQueryPool *>( pQueryPool ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::QueryPool >::type Device::createQueryPool( const VULKAN_HPP_NAMESPACE::QueryPoolCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::QueryPool  queryPool;
    Result result = static_cast<Result>( d.vkCreateQueryPool( m_device, reinterpret_cast<const VkQueryPoolCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkQueryPool *>( &queryPool ) ) );
    return createResultValue( result, queryPool, VULKAN_HPP_NAMESPACE_STRING "::Device::createQueryPool" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::QueryPool, Dispatch>>::type Device::createQueryPoolUnique( const VULKAN_HPP_NAMESPACE::QueryPoolCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::QueryPool queryPool;
    Result result = static_cast<Result>( d.vkCreateQueryPool( m_device, reinterpret_cast<const VkQueryPoolCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkQueryPool *>( &queryPool ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::QueryPool, Dispatch>( result, queryPool, VULKAN_HPP_NAMESPACE_STRING "::Device::createQueryPoolUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyQueryPool( VULKAN_HPP_NAMESPACE::QueryPool queryPool, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyQueryPool( m_device, static_cast<VkQueryPool>( queryPool ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyQueryPool( VULKAN_HPP_NAMESPACE::QueryPool queryPool, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyQueryPool( m_device, static_cast<VkQueryPool>( queryPool ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::QueryPool queryPool, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyQueryPool( m_device, static_cast<VkQueryPool>( queryPool ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::QueryPool queryPool, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyQueryPool( m_device, static_cast<VkQueryPool>( queryPool ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getQueryPoolResults( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void * pData, VULKAN_HPP_NAMESPACE::DeviceSize stride, VULKAN_HPP_NAMESPACE::QueryResultFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetQueryPoolResults( m_device, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount, dataSize, pData, static_cast<VkDeviceSize>( stride ), static_cast<VkQueryResultFlags>( flags ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<DataType,Allocator>> Device::getQueryPoolResults( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, VULKAN_HPP_NAMESPACE::DeviceSize stride, VULKAN_HPP_NAMESPACE::QueryResultFlags flags, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_ASSERT( dataSize % sizeof( DataType ) == 0 );
    std::vector<DataType,Allocator> data( dataSize / sizeof( DataType ) );
    Result result = static_cast<Result>( d.vkGetQueryPoolResults( m_device, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount, data.size() * sizeof( DataType ), reinterpret_cast<void *>( data.data() ), static_cast<VkDeviceSize>( stride ), static_cast<VkQueryResultFlags>( flags ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getQueryPoolResults", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eNotReady } );
  }

  template <typename DataType, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<DataType> Device::getQueryPoolResult( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VULKAN_HPP_NAMESPACE::DeviceSize stride, VULKAN_HPP_NAMESPACE::QueryResultFlags flags, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    DataType data;
    Result result = static_cast<Result>( d.vkGetQueryPoolResults( m_device, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount, sizeof( DataType ), reinterpret_cast<void *>( &data ), static_cast<VkDeviceSize>( stride ), static_cast<VkQueryResultFlags>( flags ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getQueryPoolResult", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eNotReady } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createBuffer( const VULKAN_HPP_NAMESPACE::BufferCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Buffer * pBuffer, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateBuffer( m_device, reinterpret_cast<const VkBufferCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkBuffer *>( pBuffer ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Buffer >::type Device::createBuffer( const VULKAN_HPP_NAMESPACE::BufferCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Buffer  buffer;
    Result result = static_cast<Result>( d.vkCreateBuffer( m_device, reinterpret_cast<const VkBufferCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkBuffer *>( &buffer ) ) );
    return createResultValue( result, buffer, VULKAN_HPP_NAMESPACE_STRING "::Device::createBuffer" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Buffer, Dispatch>>::type Device::createBufferUnique( const VULKAN_HPP_NAMESPACE::BufferCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Buffer buffer;
    Result result = static_cast<Result>( d.vkCreateBuffer( m_device, reinterpret_cast<const VkBufferCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkBuffer *>( &buffer ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Buffer, Dispatch>( result, buffer, VULKAN_HPP_NAMESPACE_STRING "::Device::createBufferUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyBuffer( VULKAN_HPP_NAMESPACE::Buffer buffer, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyBuffer( m_device, static_cast<VkBuffer>( buffer ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyBuffer( VULKAN_HPP_NAMESPACE::Buffer buffer, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyBuffer( m_device, static_cast<VkBuffer>( buffer ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Buffer buffer, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyBuffer( m_device, static_cast<VkBuffer>( buffer ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Buffer buffer, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyBuffer( m_device, static_cast<VkBuffer>( buffer ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createBufferView( const VULKAN_HPP_NAMESPACE::BufferViewCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::BufferView * pView, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateBufferView( m_device, reinterpret_cast<const VkBufferViewCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkBufferView *>( pView ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::BufferView >::type Device::createBufferView( const VULKAN_HPP_NAMESPACE::BufferViewCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::BufferView  view;
    Result result = static_cast<Result>( d.vkCreateBufferView( m_device, reinterpret_cast<const VkBufferViewCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkBufferView *>( &view ) ) );
    return createResultValue( result, view, VULKAN_HPP_NAMESPACE_STRING "::Device::createBufferView" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::BufferView, Dispatch>>::type Device::createBufferViewUnique( const VULKAN_HPP_NAMESPACE::BufferViewCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::BufferView view;
    Result result = static_cast<Result>( d.vkCreateBufferView( m_device, reinterpret_cast<const VkBufferViewCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkBufferView *>( &view ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::BufferView, Dispatch>( result, view, VULKAN_HPP_NAMESPACE_STRING "::Device::createBufferViewUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyBufferView( VULKAN_HPP_NAMESPACE::BufferView bufferView, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyBufferView( m_device, static_cast<VkBufferView>( bufferView ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyBufferView( VULKAN_HPP_NAMESPACE::BufferView bufferView, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyBufferView( m_device, static_cast<VkBufferView>( bufferView ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::BufferView bufferView, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyBufferView( m_device, static_cast<VkBufferView>( bufferView ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::BufferView bufferView, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyBufferView( m_device, static_cast<VkBufferView>( bufferView ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createImage( const VULKAN_HPP_NAMESPACE::ImageCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Image * pImage, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateImage( m_device, reinterpret_cast<const VkImageCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkImage *>( pImage ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Image >::type Device::createImage( const VULKAN_HPP_NAMESPACE::ImageCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Image  image;
    Result result = static_cast<Result>( d.vkCreateImage( m_device, reinterpret_cast<const VkImageCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkImage *>( &image ) ) );
    return createResultValue( result, image, VULKAN_HPP_NAMESPACE_STRING "::Device::createImage" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Image, Dispatch>>::type Device::createImageUnique( const VULKAN_HPP_NAMESPACE::ImageCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Image image;
    Result result = static_cast<Result>( d.vkCreateImage( m_device, reinterpret_cast<const VkImageCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkImage *>( &image ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Image, Dispatch>( result, image, VULKAN_HPP_NAMESPACE_STRING "::Device::createImageUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyImage( VULKAN_HPP_NAMESPACE::Image image, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyImage( m_device, static_cast<VkImage>( image ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyImage( VULKAN_HPP_NAMESPACE::Image image, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyImage( m_device, static_cast<VkImage>( image ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Image image, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyImage( m_device, static_cast<VkImage>( image ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Image image, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyImage( m_device, static_cast<VkImage>( image ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageSubresourceLayout( VULKAN_HPP_NAMESPACE::Image image, const VULKAN_HPP_NAMESPACE::ImageSubresource * pSubresource, VULKAN_HPP_NAMESPACE::SubresourceLayout * pLayout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageSubresourceLayout( m_device, static_cast<VkImage>( image ), reinterpret_cast<const VkImageSubresource *>( pSubresource ), reinterpret_cast<VkSubresourceLayout *>( pLayout ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::SubresourceLayout  Device::getImageSubresourceLayout( VULKAN_HPP_NAMESPACE::Image image, const VULKAN_HPP_NAMESPACE::ImageSubresource & subresource, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SubresourceLayout  layout;
    d.vkGetImageSubresourceLayout( m_device, static_cast<VkImage>( image ), reinterpret_cast<const VkImageSubresource *>( &subresource ), reinterpret_cast<VkSubresourceLayout *>( &layout ) );
    return layout;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createImageView( const VULKAN_HPP_NAMESPACE::ImageViewCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::ImageView * pView, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateImageView( m_device, reinterpret_cast<const VkImageViewCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkImageView *>( pView ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ImageView >::type Device::createImageView( const VULKAN_HPP_NAMESPACE::ImageViewCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ImageView  view;
    Result result = static_cast<Result>( d.vkCreateImageView( m_device, reinterpret_cast<const VkImageViewCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkImageView *>( &view ) ) );
    return createResultValue( result, view, VULKAN_HPP_NAMESPACE_STRING "::Device::createImageView" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::ImageView, Dispatch>>::type Device::createImageViewUnique( const VULKAN_HPP_NAMESPACE::ImageViewCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::ImageView view;
    Result result = static_cast<Result>( d.vkCreateImageView( m_device, reinterpret_cast<const VkImageViewCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkImageView *>( &view ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::ImageView, Dispatch>( result, view, VULKAN_HPP_NAMESPACE_STRING "::Device::createImageViewUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyImageView( VULKAN_HPP_NAMESPACE::ImageView imageView, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyImageView( m_device, static_cast<VkImageView>( imageView ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyImageView( VULKAN_HPP_NAMESPACE::ImageView imageView, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyImageView( m_device, static_cast<VkImageView>( imageView ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::ImageView imageView, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyImageView( m_device, static_cast<VkImageView>( imageView ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::ImageView imageView, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyImageView( m_device, static_cast<VkImageView>( imageView ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createShaderModule( const VULKAN_HPP_NAMESPACE::ShaderModuleCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::ShaderModule * pShaderModule, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateShaderModule( m_device, reinterpret_cast<const VkShaderModuleCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkShaderModule *>( pShaderModule ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ShaderModule >::type Device::createShaderModule( const VULKAN_HPP_NAMESPACE::ShaderModuleCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ShaderModule  shaderModule;
    Result result = static_cast<Result>( d.vkCreateShaderModule( m_device, reinterpret_cast<const VkShaderModuleCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkShaderModule *>( &shaderModule ) ) );
    return createResultValue( result, shaderModule, VULKAN_HPP_NAMESPACE_STRING "::Device::createShaderModule" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::ShaderModule, Dispatch>>::type Device::createShaderModuleUnique( const VULKAN_HPP_NAMESPACE::ShaderModuleCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::ShaderModule shaderModule;
    Result result = static_cast<Result>( d.vkCreateShaderModule( m_device, reinterpret_cast<const VkShaderModuleCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkShaderModule *>( &shaderModule ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::ShaderModule, Dispatch>( result, shaderModule, VULKAN_HPP_NAMESPACE_STRING "::Device::createShaderModuleUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyShaderModule( VULKAN_HPP_NAMESPACE::ShaderModule shaderModule, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyShaderModule( m_device, static_cast<VkShaderModule>( shaderModule ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyShaderModule( VULKAN_HPP_NAMESPACE::ShaderModule shaderModule, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyShaderModule( m_device, static_cast<VkShaderModule>( shaderModule ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::ShaderModule shaderModule, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyShaderModule( m_device, static_cast<VkShaderModule>( shaderModule ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::ShaderModule shaderModule, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyShaderModule( m_device, static_cast<VkShaderModule>( shaderModule ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createPipelineCache( const VULKAN_HPP_NAMESPACE::PipelineCacheCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::PipelineCache * pPipelineCache, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreatePipelineCache( m_device, reinterpret_cast<const VkPipelineCacheCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPipelineCache *>( pPipelineCache ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::PipelineCache >::type Device::createPipelineCache( const VULKAN_HPP_NAMESPACE::PipelineCacheCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PipelineCache  pipelineCache;
    Result result = static_cast<Result>( d.vkCreatePipelineCache( m_device, reinterpret_cast<const VkPipelineCacheCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipelineCache *>( &pipelineCache ) ) );
    return createResultValue( result, pipelineCache, VULKAN_HPP_NAMESPACE_STRING "::Device::createPipelineCache" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::PipelineCache, Dispatch>>::type Device::createPipelineCacheUnique( const VULKAN_HPP_NAMESPACE::PipelineCacheCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache;
    Result result = static_cast<Result>( d.vkCreatePipelineCache( m_device, reinterpret_cast<const VkPipelineCacheCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipelineCache *>( &pipelineCache ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::PipelineCache, Dispatch>( result, pipelineCache, VULKAN_HPP_NAMESPACE_STRING "::Device::createPipelineCacheUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPipelineCache( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPipelineCache( m_device, static_cast<VkPipelineCache>( pipelineCache ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPipelineCache( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPipelineCache( m_device, static_cast<VkPipelineCache>( pipelineCache ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPipelineCache( m_device, static_cast<VkPipelineCache>( pipelineCache ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPipelineCache( m_device, static_cast<VkPipelineCache>( pipelineCache ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getPipelineCacheData( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, size_t * pDataSize, void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPipelineCacheData( m_device, static_cast<VkPipelineCache>( pipelineCache ), pDataSize, pData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Uint8_tAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<uint8_t, Uint8_tAllocator>>::type Device::getPipelineCacheData( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<uint8_t, Uint8_tAllocator> data;
    size_t dataSize;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineCacheData( m_device, static_cast<VkPipelineCache>( pipelineCache ), &dataSize, nullptr ) );
      if ( ( result == Result::eSuccess ) && dataSize )
      {
        data.resize( dataSize );
        result = static_cast<Result>( d.vkGetPipelineCacheData( m_device, static_cast<VkPipelineCache>( pipelineCache ), &dataSize, reinterpret_cast<void *>( data.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( dataSize <= data.size() );
      if ( dataSize < data.size() )
      {
        data.resize( dataSize );
      }
    }
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineCacheData" );
  }

  template <typename Uint8_tAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, uint8_t>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<uint8_t, Uint8_tAllocator>>::type Device::getPipelineCacheData( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, Uint8_tAllocator & uint8_tAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<uint8_t, Uint8_tAllocator> data( uint8_tAllocator );
    size_t dataSize;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineCacheData( m_device, static_cast<VkPipelineCache>( pipelineCache ), &dataSize, nullptr ) );
      if ( ( result == Result::eSuccess ) && dataSize )
      {
        data.resize( dataSize );
        result = static_cast<Result>( d.vkGetPipelineCacheData( m_device, static_cast<VkPipelineCache>( pipelineCache ), &dataSize, reinterpret_cast<void *>( data.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( dataSize <= data.size() );
      if ( dataSize < data.size() )
      {
        data.resize( dataSize );
      }
    }
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineCacheData" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::mergePipelineCaches( VULKAN_HPP_NAMESPACE::PipelineCache dstCache, uint32_t srcCacheCount, const VULKAN_HPP_NAMESPACE::PipelineCache * pSrcCaches, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkMergePipelineCaches( m_device, static_cast<VkPipelineCache>( dstCache ), srcCacheCount, reinterpret_cast<const VkPipelineCache *>( pSrcCaches ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::mergePipelineCaches( VULKAN_HPP_NAMESPACE::PipelineCache dstCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::PipelineCache> const & srcCaches, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkMergePipelineCaches( m_device, static_cast<VkPipelineCache>( dstCache ), srcCaches.size(), reinterpret_cast<const VkPipelineCache *>( srcCaches.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::mergePipelineCaches" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createGraphicsPipelines( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, uint32_t createInfoCount, const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo * pCreateInfos, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Pipeline * pPipelines, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfoCount, reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( pCreateInfos ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPipeline *>( pPipelines ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createGraphicsPipelines( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createGraphicsPipelines", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename PipelineAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, Pipeline>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createGraphicsPipelines( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size(), pipelineAllocator );
    Result result = static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createGraphicsPipelines", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<VULKAN_HPP_NAMESPACE::Pipeline > Device::createGraphicsPipeline( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Pipeline  pipeline;
    Result result = static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    return createResultValue( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createGraphicsPipeline", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename PipelineAllocator>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createGraphicsPipelinesUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines;
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createGraphicsPipelinesUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch, typename PipelineAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<Pipeline, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createGraphicsPipelinesUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines( pipelineAllocator );
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createGraphicsPipelinesUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<UniqueHandle<Pipeline, Dispatch>> Device::createGraphicsPipelineUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::GraphicsPipelineCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    Pipeline pipeline;
    Result result = static_cast<Result>( d.vkCreateGraphicsPipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkGraphicsPipelineCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<Pipeline, Dispatch>( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createGraphicsPipelineUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT }, deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createComputePipelines( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, uint32_t createInfoCount, const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo * pCreateInfos, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Pipeline * pPipelines, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfoCount, reinterpret_cast<const VkComputePipelineCreateInfo *>( pCreateInfos ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPipeline *>( pPipelines ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createComputePipelines( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkComputePipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createComputePipelines", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename PipelineAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, Pipeline>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createComputePipelines( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size(), pipelineAllocator );
    Result result = static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkComputePipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createComputePipelines", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<VULKAN_HPP_NAMESPACE::Pipeline > Device::createComputePipeline( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Pipeline  pipeline;
    Result result = static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkComputePipelineCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    return createResultValue( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createComputePipeline", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename PipelineAllocator>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createComputePipelinesUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines;
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkComputePipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createComputePipelinesUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch, typename PipelineAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<Pipeline, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createComputePipelinesUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines( pipelineAllocator );
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkComputePipelineCreateInfo *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createComputePipelinesUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<UniqueHandle<Pipeline, Dispatch>> Device::createComputePipelineUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::ComputePipelineCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    Pipeline pipeline;
    Result result = static_cast<Result>( d.vkCreateComputePipelines( m_device, static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkComputePipelineCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<Pipeline, Dispatch>( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createComputePipelineUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT }, deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPipeline( VULKAN_HPP_NAMESPACE::Pipeline pipeline, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPipeline( m_device, static_cast<VkPipeline>( pipeline ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPipeline( VULKAN_HPP_NAMESPACE::Pipeline pipeline, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPipeline( m_device, static_cast<VkPipeline>( pipeline ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Pipeline pipeline, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPipeline( m_device, static_cast<VkPipeline>( pipeline ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Pipeline pipeline, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPipeline( m_device, static_cast<VkPipeline>( pipeline ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createPipelineLayout( const VULKAN_HPP_NAMESPACE::PipelineLayoutCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::PipelineLayout * pPipelineLayout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreatePipelineLayout( m_device, reinterpret_cast<const VkPipelineLayoutCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPipelineLayout *>( pPipelineLayout ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::PipelineLayout >::type Device::createPipelineLayout( const VULKAN_HPP_NAMESPACE::PipelineLayoutCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PipelineLayout  pipelineLayout;
    Result result = static_cast<Result>( d.vkCreatePipelineLayout( m_device, reinterpret_cast<const VkPipelineLayoutCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipelineLayout *>( &pipelineLayout ) ) );
    return createResultValue( result, pipelineLayout, VULKAN_HPP_NAMESPACE_STRING "::Device::createPipelineLayout" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::PipelineLayout, Dispatch>>::type Device::createPipelineLayoutUnique( const VULKAN_HPP_NAMESPACE::PipelineLayoutCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::PipelineLayout pipelineLayout;
    Result result = static_cast<Result>( d.vkCreatePipelineLayout( m_device, reinterpret_cast<const VkPipelineLayoutCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipelineLayout *>( &pipelineLayout ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::PipelineLayout, Dispatch>( result, pipelineLayout, VULKAN_HPP_NAMESPACE_STRING "::Device::createPipelineLayoutUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPipelineLayout( VULKAN_HPP_NAMESPACE::PipelineLayout pipelineLayout, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPipelineLayout( m_device, static_cast<VkPipelineLayout>( pipelineLayout ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPipelineLayout( VULKAN_HPP_NAMESPACE::PipelineLayout pipelineLayout, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPipelineLayout( m_device, static_cast<VkPipelineLayout>( pipelineLayout ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::PipelineLayout pipelineLayout, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPipelineLayout( m_device, static_cast<VkPipelineLayout>( pipelineLayout ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::PipelineLayout pipelineLayout, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPipelineLayout( m_device, static_cast<VkPipelineLayout>( pipelineLayout ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createSampler( const VULKAN_HPP_NAMESPACE::SamplerCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Sampler * pSampler, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateSampler( m_device, reinterpret_cast<const VkSamplerCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSampler *>( pSampler ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Sampler >::type Device::createSampler( const VULKAN_HPP_NAMESPACE::SamplerCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Sampler  sampler;
    Result result = static_cast<Result>( d.vkCreateSampler( m_device, reinterpret_cast<const VkSamplerCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSampler *>( &sampler ) ) );
    return createResultValue( result, sampler, VULKAN_HPP_NAMESPACE_STRING "::Device::createSampler" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Sampler, Dispatch>>::type Device::createSamplerUnique( const VULKAN_HPP_NAMESPACE::SamplerCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Sampler sampler;
    Result result = static_cast<Result>( d.vkCreateSampler( m_device, reinterpret_cast<const VkSamplerCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSampler *>( &sampler ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Sampler, Dispatch>( result, sampler, VULKAN_HPP_NAMESPACE_STRING "::Device::createSamplerUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySampler( VULKAN_HPP_NAMESPACE::Sampler sampler, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySampler( m_device, static_cast<VkSampler>( sampler ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySampler( VULKAN_HPP_NAMESPACE::Sampler sampler, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySampler( m_device, static_cast<VkSampler>( sampler ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Sampler sampler, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySampler( m_device, static_cast<VkSampler>( sampler ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Sampler sampler, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySampler( m_device, static_cast<VkSampler>( sampler ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createDescriptorSetLayout( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DescriptorSetLayout * pSetLayout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDescriptorSetLayout( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDescriptorSetLayout *>( pSetLayout ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DescriptorSetLayout >::type Device::createDescriptorSetLayout( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorSetLayout  setLayout;
    Result result = static_cast<Result>( d.vkCreateDescriptorSetLayout( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorSetLayout *>( &setLayout ) ) );
    return createResultValue( result, setLayout, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorSetLayout" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DescriptorSetLayout, Dispatch>>::type Device::createDescriptorSetLayoutUnique( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DescriptorSetLayout setLayout;
    Result result = static_cast<Result>( d.vkCreateDescriptorSetLayout( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorSetLayout *>( &setLayout ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DescriptorSetLayout, Dispatch>( result, setLayout, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorSetLayoutUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorSetLayout( VULKAN_HPP_NAMESPACE::DescriptorSetLayout descriptorSetLayout, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorSetLayout( m_device, static_cast<VkDescriptorSetLayout>( descriptorSetLayout ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorSetLayout( VULKAN_HPP_NAMESPACE::DescriptorSetLayout descriptorSetLayout, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorSetLayout( m_device, static_cast<VkDescriptorSetLayout>( descriptorSetLayout ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DescriptorSetLayout descriptorSetLayout, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorSetLayout( m_device, static_cast<VkDescriptorSetLayout>( descriptorSetLayout ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DescriptorSetLayout descriptorSetLayout, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorSetLayout( m_device, static_cast<VkDescriptorSetLayout>( descriptorSetLayout ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createDescriptorPool( const VULKAN_HPP_NAMESPACE::DescriptorPoolCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DescriptorPool * pDescriptorPool, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDescriptorPool( m_device, reinterpret_cast<const VkDescriptorPoolCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDescriptorPool *>( pDescriptorPool ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DescriptorPool >::type Device::createDescriptorPool( const VULKAN_HPP_NAMESPACE::DescriptorPoolCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorPool  descriptorPool;
    Result result = static_cast<Result>( d.vkCreateDescriptorPool( m_device, reinterpret_cast<const VkDescriptorPoolCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorPool *>( &descriptorPool ) ) );
    return createResultValue( result, descriptorPool, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorPool" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DescriptorPool, Dispatch>>::type Device::createDescriptorPoolUnique( const VULKAN_HPP_NAMESPACE::DescriptorPoolCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool;
    Result result = static_cast<Result>( d.vkCreateDescriptorPool( m_device, reinterpret_cast<const VkDescriptorPoolCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorPool *>( &descriptorPool ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DescriptorPool, Dispatch>( result, descriptorPool, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorPoolUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorPool( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorPool( m_device, static_cast<VkDescriptorPool>( descriptorPool ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorPool( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorPool( m_device, static_cast<VkDescriptorPool>( descriptorPool ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorPool( m_device, static_cast<VkDescriptorPool>( descriptorPool ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorPool( m_device, static_cast<VkDescriptorPool>( descriptorPool ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Result Device::resetDescriptorPool( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, VULKAN_HPP_NAMESPACE::DescriptorPoolResetFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkResetDescriptorPool( m_device, static_cast<VkDescriptorPool>( descriptorPool ), static_cast<VkDescriptorPoolResetFlags>( flags ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::resetDescriptorPool( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, VULKAN_HPP_NAMESPACE::DescriptorPoolResetFlags flags, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkResetDescriptorPool( m_device, static_cast<VkDescriptorPool>( descriptorPool ), static_cast<VkDescriptorPoolResetFlags>( flags ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::resetDescriptorPool" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::allocateDescriptorSets( const VULKAN_HPP_NAMESPACE::DescriptorSetAllocateInfo * pAllocateInfo, VULKAN_HPP_NAMESPACE::DescriptorSet * pDescriptorSets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAllocateDescriptorSets( m_device, reinterpret_cast<const VkDescriptorSetAllocateInfo *>( pAllocateInfo ), reinterpret_cast<VkDescriptorSet *>( pDescriptorSets ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DescriptorSetAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<VULKAN_HPP_NAMESPACE::DescriptorSet, DescriptorSetAllocator>>::type Device::allocateDescriptorSets( const VULKAN_HPP_NAMESPACE::DescriptorSetAllocateInfo & allocateInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::DescriptorSet, DescriptorSetAllocator> descriptorSets( allocateInfo.descriptorSetCount );
    Result result = static_cast<Result>( d.vkAllocateDescriptorSets( m_device, reinterpret_cast<const VkDescriptorSetAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkDescriptorSet *>( descriptorSets.data() ) ) );
    return createResultValue( result, descriptorSets, VULKAN_HPP_NAMESPACE_STRING "::Device::allocateDescriptorSets" );
  }

  template <typename DescriptorSetAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DescriptorSet>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<VULKAN_HPP_NAMESPACE::DescriptorSet, DescriptorSetAllocator>>::type Device::allocateDescriptorSets( const VULKAN_HPP_NAMESPACE::DescriptorSetAllocateInfo & allocateInfo, DescriptorSetAllocator & descriptorSetAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::DescriptorSet, DescriptorSetAllocator> descriptorSets( allocateInfo.descriptorSetCount, descriptorSetAllocator );
    Result result = static_cast<Result>( d.vkAllocateDescriptorSets( m_device, reinterpret_cast<const VkDescriptorSetAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkDescriptorSet *>( descriptorSets.data() ) ) );
    return createResultValue( result, descriptorSets, VULKAN_HPP_NAMESPACE_STRING "::Device::allocateDescriptorSets" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename DescriptorSetAllocator>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<UniqueHandle<DescriptorSet, Dispatch>, DescriptorSetAllocator>>::type Device::allocateDescriptorSetsUnique( const VULKAN_HPP_NAMESPACE::DescriptorSetAllocateInfo & allocateInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<DescriptorSet, Dispatch>, DescriptorSetAllocator> uniqueDescriptorSets;
    std::vector<DescriptorSet> descriptorSets( allocateInfo.descriptorSetCount );
    Result result = static_cast<Result>( d.vkAllocateDescriptorSets( m_device, reinterpret_cast<const VkDescriptorSetAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkDescriptorSet *>( descriptorSets.data() ) ) );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      uniqueDescriptorSets.reserve( allocateInfo.descriptorSetCount );
      PoolFree<Device, DescriptorPool, Dispatch> deleter( *this, allocateInfo.descriptorPool, d );
      for ( size_t i=0; i < allocateInfo.descriptorSetCount; i++ )
      {
        uniqueDescriptorSets.push_back( UniqueHandle<DescriptorSet, Dispatch>( descriptorSets[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniqueDescriptorSets ), VULKAN_HPP_NAMESPACE_STRING "::Device::allocateDescriptorSetsUnique" );
  }

  template <typename Dispatch, typename DescriptorSetAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<DescriptorSet, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<UniqueHandle<DescriptorSet, Dispatch>, DescriptorSetAllocator>>::type Device::allocateDescriptorSetsUnique( const VULKAN_HPP_NAMESPACE::DescriptorSetAllocateInfo & allocateInfo, DescriptorSetAllocator & descriptorSetAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<DescriptorSet, Dispatch>, DescriptorSetAllocator> uniqueDescriptorSets( descriptorSetAllocator );
    std::vector<DescriptorSet> descriptorSets( allocateInfo.descriptorSetCount );
    Result result = static_cast<Result>( d.vkAllocateDescriptorSets( m_device, reinterpret_cast<const VkDescriptorSetAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkDescriptorSet *>( descriptorSets.data() ) ) );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      uniqueDescriptorSets.reserve( allocateInfo.descriptorSetCount );
      PoolFree<Device, DescriptorPool, Dispatch> deleter( *this, allocateInfo.descriptorPool, d );
      for ( size_t i=0; i < allocateInfo.descriptorSetCount; i++ )
      {
        uniqueDescriptorSets.push_back( UniqueHandle<DescriptorSet, Dispatch>( descriptorSets[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniqueDescriptorSets ), VULKAN_HPP_NAMESPACE_STRING "::Device::allocateDescriptorSetsUnique" );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Result Device::freeDescriptorSets( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, uint32_t descriptorSetCount, const VULKAN_HPP_NAMESPACE::DescriptorSet * pDescriptorSets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkFreeDescriptorSets( m_device, static_cast<VkDescriptorPool>( descriptorPool ), descriptorSetCount, reinterpret_cast<const VkDescriptorSet *>( pDescriptorSets ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::freeDescriptorSets( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, ArrayProxy<const VULKAN_HPP_NAMESPACE::DescriptorSet> const & descriptorSets, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkFreeDescriptorSets( m_device, static_cast<VkDescriptorPool>( descriptorPool ), descriptorSets.size(), reinterpret_cast<const VkDescriptorSet *>( descriptorSets.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::freeDescriptorSets" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Result ( Device::free )( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, uint32_t descriptorSetCount, const VULKAN_HPP_NAMESPACE::DescriptorSet * pDescriptorSets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkFreeDescriptorSets( m_device, static_cast<VkDescriptorPool>( descriptorPool ), descriptorSetCount, reinterpret_cast<const VkDescriptorSet *>( pDescriptorSets ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type ( Device::free )( VULKAN_HPP_NAMESPACE::DescriptorPool descriptorPool, ArrayProxy<const VULKAN_HPP_NAMESPACE::DescriptorSet> const & descriptorSets, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkFreeDescriptorSets( m_device, static_cast<VkDescriptorPool>( descriptorPool ), descriptorSets.size(), reinterpret_cast<const VkDescriptorSet *>( descriptorSets.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::( Device::free )" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::updateDescriptorSets( uint32_t descriptorWriteCount, const VULKAN_HPP_NAMESPACE::WriteDescriptorSet * pDescriptorWrites, uint32_t descriptorCopyCount, const VULKAN_HPP_NAMESPACE::CopyDescriptorSet * pDescriptorCopies, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkUpdateDescriptorSets( m_device, descriptorWriteCount, reinterpret_cast<const VkWriteDescriptorSet *>( pDescriptorWrites ), descriptorCopyCount, reinterpret_cast<const VkCopyDescriptorSet *>( pDescriptorCopies ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::updateDescriptorSets( ArrayProxy<const VULKAN_HPP_NAMESPACE::WriteDescriptorSet> const & descriptorWrites, ArrayProxy<const VULKAN_HPP_NAMESPACE::CopyDescriptorSet> const & descriptorCopies, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkUpdateDescriptorSets( m_device, descriptorWrites.size(), reinterpret_cast<const VkWriteDescriptorSet *>( descriptorWrites.data() ), descriptorCopies.size(), reinterpret_cast<const VkCopyDescriptorSet *>( descriptorCopies.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createFramebuffer( const VULKAN_HPP_NAMESPACE::FramebufferCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Framebuffer * pFramebuffer, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateFramebuffer( m_device, reinterpret_cast<const VkFramebufferCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkFramebuffer *>( pFramebuffer ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Framebuffer >::type Device::createFramebuffer( const VULKAN_HPP_NAMESPACE::FramebufferCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Framebuffer  framebuffer;
    Result result = static_cast<Result>( d.vkCreateFramebuffer( m_device, reinterpret_cast<const VkFramebufferCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFramebuffer *>( &framebuffer ) ) );
    return createResultValue( result, framebuffer, VULKAN_HPP_NAMESPACE_STRING "::Device::createFramebuffer" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Framebuffer, Dispatch>>::type Device::createFramebufferUnique( const VULKAN_HPP_NAMESPACE::FramebufferCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Framebuffer framebuffer;
    Result result = static_cast<Result>( d.vkCreateFramebuffer( m_device, reinterpret_cast<const VkFramebufferCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFramebuffer *>( &framebuffer ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Framebuffer, Dispatch>( result, framebuffer, VULKAN_HPP_NAMESPACE_STRING "::Device::createFramebufferUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyFramebuffer( VULKAN_HPP_NAMESPACE::Framebuffer framebuffer, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyFramebuffer( m_device, static_cast<VkFramebuffer>( framebuffer ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyFramebuffer( VULKAN_HPP_NAMESPACE::Framebuffer framebuffer, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyFramebuffer( m_device, static_cast<VkFramebuffer>( framebuffer ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Framebuffer framebuffer, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyFramebuffer( m_device, static_cast<VkFramebuffer>( framebuffer ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::Framebuffer framebuffer, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyFramebuffer( m_device, static_cast<VkFramebuffer>( framebuffer ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createRenderPass( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::RenderPass * pRenderPass, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateRenderPass( m_device, reinterpret_cast<const VkRenderPassCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkRenderPass *>( pRenderPass ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::RenderPass >::type Device::createRenderPass( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::RenderPass  renderPass;
    Result result = static_cast<Result>( d.vkCreateRenderPass( m_device, reinterpret_cast<const VkRenderPassCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkRenderPass *>( &renderPass ) ) );
    return createResultValue( result, renderPass, VULKAN_HPP_NAMESPACE_STRING "::Device::createRenderPass" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::RenderPass, Dispatch>>::type Device::createRenderPassUnique( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::RenderPass renderPass;
    Result result = static_cast<Result>( d.vkCreateRenderPass( m_device, reinterpret_cast<const VkRenderPassCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkRenderPass *>( &renderPass ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::RenderPass, Dispatch>( result, renderPass, VULKAN_HPP_NAMESPACE_STRING "::Device::createRenderPassUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyRenderPass( VULKAN_HPP_NAMESPACE::RenderPass renderPass, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyRenderPass( m_device, static_cast<VkRenderPass>( renderPass ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyRenderPass( VULKAN_HPP_NAMESPACE::RenderPass renderPass, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyRenderPass( m_device, static_cast<VkRenderPass>( renderPass ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::RenderPass renderPass, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyRenderPass( m_device, static_cast<VkRenderPass>( renderPass ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::RenderPass renderPass, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyRenderPass( m_device, static_cast<VkRenderPass>( renderPass ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getRenderAreaGranularity( VULKAN_HPP_NAMESPACE::RenderPass renderPass, VULKAN_HPP_NAMESPACE::Extent2D * pGranularity, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetRenderAreaGranularity( m_device, static_cast<VkRenderPass>( renderPass ), reinterpret_cast<VkExtent2D *>( pGranularity ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::Extent2D  Device::getRenderAreaGranularity( VULKAN_HPP_NAMESPACE::RenderPass renderPass, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Extent2D  granularity;
    d.vkGetRenderAreaGranularity( m_device, static_cast<VkRenderPass>( renderPass ), reinterpret_cast<VkExtent2D *>( &granularity ) );
    return granularity;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createCommandPool( const VULKAN_HPP_NAMESPACE::CommandPoolCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::CommandPool * pCommandPool, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateCommandPool( m_device, reinterpret_cast<const VkCommandPoolCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkCommandPool *>( pCommandPool ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::CommandPool >::type Device::createCommandPool( const VULKAN_HPP_NAMESPACE::CommandPoolCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::CommandPool  commandPool;
    Result result = static_cast<Result>( d.vkCreateCommandPool( m_device, reinterpret_cast<const VkCommandPoolCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkCommandPool *>( &commandPool ) ) );
    return createResultValue( result, commandPool, VULKAN_HPP_NAMESPACE_STRING "::Device::createCommandPool" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::CommandPool, Dispatch>>::type Device::createCommandPoolUnique( const VULKAN_HPP_NAMESPACE::CommandPoolCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::CommandPool commandPool;
    Result result = static_cast<Result>( d.vkCreateCommandPool( m_device, reinterpret_cast<const VkCommandPoolCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkCommandPool *>( &commandPool ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::CommandPool, Dispatch>( result, commandPool, VULKAN_HPP_NAMESPACE_STRING "::Device::createCommandPoolUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyCommandPool( VULKAN_HPP_NAMESPACE::CommandPool commandPool, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyCommandPool( VULKAN_HPP_NAMESPACE::CommandPool commandPool, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::CommandPool commandPool, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::CommandPool commandPool, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::resetCommandPool( VULKAN_HPP_NAMESPACE::CommandPool commandPool, VULKAN_HPP_NAMESPACE::CommandPoolResetFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkResetCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), static_cast<VkCommandPoolResetFlags>( flags ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::resetCommandPool( VULKAN_HPP_NAMESPACE::CommandPool commandPool, VULKAN_HPP_NAMESPACE::CommandPoolResetFlags flags, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkResetCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), static_cast<VkCommandPoolResetFlags>( flags ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::resetCommandPool" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::allocateCommandBuffers( const VULKAN_HPP_NAMESPACE::CommandBufferAllocateInfo * pAllocateInfo, VULKAN_HPP_NAMESPACE::CommandBuffer * pCommandBuffers, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAllocateCommandBuffers( m_device, reinterpret_cast<const VkCommandBufferAllocateInfo *>( pAllocateInfo ), reinterpret_cast<VkCommandBuffer *>( pCommandBuffers ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename CommandBufferAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<VULKAN_HPP_NAMESPACE::CommandBuffer, CommandBufferAllocator>>::type Device::allocateCommandBuffers( const VULKAN_HPP_NAMESPACE::CommandBufferAllocateInfo & allocateInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::CommandBuffer, CommandBufferAllocator> commandBuffers( allocateInfo.commandBufferCount );
    Result result = static_cast<Result>( d.vkAllocateCommandBuffers( m_device, reinterpret_cast<const VkCommandBufferAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkCommandBuffer *>( commandBuffers.data() ) ) );
    return createResultValue( result, commandBuffers, VULKAN_HPP_NAMESPACE_STRING "::Device::allocateCommandBuffers" );
  }

  template <typename CommandBufferAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, CommandBuffer>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<VULKAN_HPP_NAMESPACE::CommandBuffer, CommandBufferAllocator>>::type Device::allocateCommandBuffers( const VULKAN_HPP_NAMESPACE::CommandBufferAllocateInfo & allocateInfo, CommandBufferAllocator & commandBufferAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::CommandBuffer, CommandBufferAllocator> commandBuffers( allocateInfo.commandBufferCount, commandBufferAllocator );
    Result result = static_cast<Result>( d.vkAllocateCommandBuffers( m_device, reinterpret_cast<const VkCommandBufferAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkCommandBuffer *>( commandBuffers.data() ) ) );
    return createResultValue( result, commandBuffers, VULKAN_HPP_NAMESPACE_STRING "::Device::allocateCommandBuffers" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename CommandBufferAllocator>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<UniqueHandle<CommandBuffer, Dispatch>, CommandBufferAllocator>>::type Device::allocateCommandBuffersUnique( const VULKAN_HPP_NAMESPACE::CommandBufferAllocateInfo & allocateInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<CommandBuffer, Dispatch>, CommandBufferAllocator> uniqueCommandBuffers;
    std::vector<CommandBuffer> commandBuffers( allocateInfo.commandBufferCount );
    Result result = static_cast<Result>( d.vkAllocateCommandBuffers( m_device, reinterpret_cast<const VkCommandBufferAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkCommandBuffer *>( commandBuffers.data() ) ) );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      uniqueCommandBuffers.reserve( allocateInfo.commandBufferCount );
      PoolFree<Device, CommandPool, Dispatch> deleter( *this, allocateInfo.commandPool, d );
      for ( size_t i=0; i < allocateInfo.commandBufferCount; i++ )
      {
        uniqueCommandBuffers.push_back( UniqueHandle<CommandBuffer, Dispatch>( commandBuffers[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniqueCommandBuffers ), VULKAN_HPP_NAMESPACE_STRING "::Device::allocateCommandBuffersUnique" );
  }

  template <typename Dispatch, typename CommandBufferAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<CommandBuffer, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<UniqueHandle<CommandBuffer, Dispatch>, CommandBufferAllocator>>::type Device::allocateCommandBuffersUnique( const VULKAN_HPP_NAMESPACE::CommandBufferAllocateInfo & allocateInfo, CommandBufferAllocator & commandBufferAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<CommandBuffer, Dispatch>, CommandBufferAllocator> uniqueCommandBuffers( commandBufferAllocator );
    std::vector<CommandBuffer> commandBuffers( allocateInfo.commandBufferCount );
    Result result = static_cast<Result>( d.vkAllocateCommandBuffers( m_device, reinterpret_cast<const VkCommandBufferAllocateInfo *>( &allocateInfo ), reinterpret_cast<VkCommandBuffer *>( commandBuffers.data() ) ) );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      uniqueCommandBuffers.reserve( allocateInfo.commandBufferCount );
      PoolFree<Device, CommandPool, Dispatch> deleter( *this, allocateInfo.commandPool, d );
      for ( size_t i=0; i < allocateInfo.commandBufferCount; i++ )
      {
        uniqueCommandBuffers.push_back( UniqueHandle<CommandBuffer, Dispatch>( commandBuffers[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniqueCommandBuffers ), VULKAN_HPP_NAMESPACE_STRING "::Device::allocateCommandBuffersUnique" );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::freeCommandBuffers( VULKAN_HPP_NAMESPACE::CommandPool commandPool, uint32_t commandBufferCount, const VULKAN_HPP_NAMESPACE::CommandBuffer * pCommandBuffers, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkFreeCommandBuffers( m_device, static_cast<VkCommandPool>( commandPool ), commandBufferCount, reinterpret_cast<const VkCommandBuffer *>( pCommandBuffers ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::freeCommandBuffers( VULKAN_HPP_NAMESPACE::CommandPool commandPool, ArrayProxy<const VULKAN_HPP_NAMESPACE::CommandBuffer> const & commandBuffers, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkFreeCommandBuffers( m_device, static_cast<VkCommandPool>( commandPool ), commandBuffers.size(), reinterpret_cast<const VkCommandBuffer *>( commandBuffers.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void ( Device::free )( VULKAN_HPP_NAMESPACE::CommandPool commandPool, uint32_t commandBufferCount, const VULKAN_HPP_NAMESPACE::CommandBuffer * pCommandBuffers, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkFreeCommandBuffers( m_device, static_cast<VkCommandPool>( commandPool ), commandBufferCount, reinterpret_cast<const VkCommandBuffer *>( pCommandBuffers ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void ( Device::free )( VULKAN_HPP_NAMESPACE::CommandPool commandPool, ArrayProxy<const VULKAN_HPP_NAMESPACE::CommandBuffer> const & commandBuffers, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkFreeCommandBuffers( m_device, static_cast<VkCommandPool>( commandPool ), commandBuffers.size(), reinterpret_cast<const VkCommandBuffer *>( commandBuffers.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result CommandBuffer::begin( const VULKAN_HPP_NAMESPACE::CommandBufferBeginInfo * pBeginInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBeginCommandBuffer( m_commandBuffer, reinterpret_cast<const VkCommandBufferBeginInfo *>( pBeginInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type CommandBuffer::begin( const VULKAN_HPP_NAMESPACE::CommandBufferBeginInfo & beginInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBeginCommandBuffer( m_commandBuffer, reinterpret_cast<const VkCommandBufferBeginInfo *>( &beginInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::begin" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result CommandBuffer::end( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEndCommandBuffer( m_commandBuffer ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type CommandBuffer::end( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkEndCommandBuffer( m_commandBuffer ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::end" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result CommandBuffer::reset( VULKAN_HPP_NAMESPACE::CommandBufferResetFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkResetCommandBuffer( m_commandBuffer, static_cast<VkCommandBufferResetFlags>( flags ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type CommandBuffer::reset( VULKAN_HPP_NAMESPACE::CommandBufferResetFlags flags, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkResetCommandBuffer( m_commandBuffer, static_cast<VkCommandBufferResetFlags>( flags ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::reset" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindPipeline( VULKAN_HPP_NAMESPACE::PipelineBindPoint pipelineBindPoint, VULKAN_HPP_NAMESPACE::Pipeline pipeline, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindPipeline( m_commandBuffer, static_cast<VkPipelineBindPoint>( pipelineBindPoint ), static_cast<VkPipeline>( pipeline ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewport( uint32_t firstViewport, uint32_t viewportCount, const VULKAN_HPP_NAMESPACE::Viewport * pViewports, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetViewport( m_commandBuffer, firstViewport, viewportCount, reinterpret_cast<const VkViewport *>( pViewports ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewport( uint32_t firstViewport, ArrayProxy<const VULKAN_HPP_NAMESPACE::Viewport> const & viewports, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetViewport( m_commandBuffer, firstViewport, viewports.size(), reinterpret_cast<const VkViewport *>( viewports.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setScissor( uint32_t firstScissor, uint32_t scissorCount, const VULKAN_HPP_NAMESPACE::Rect2D * pScissors, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetScissor( m_commandBuffer, firstScissor, scissorCount, reinterpret_cast<const VkRect2D *>( pScissors ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setScissor( uint32_t firstScissor, ArrayProxy<const VULKAN_HPP_NAMESPACE::Rect2D> const & scissors, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetScissor( m_commandBuffer, firstScissor, scissors.size(), reinterpret_cast<const VkRect2D *>( scissors.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setLineWidth( float lineWidth, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetLineWidth( m_commandBuffer, lineWidth );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthBias( float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthBias( m_commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setBlendConstants( const float blendConstants[4], Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetBlendConstants( m_commandBuffer, blendConstants );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthBounds( float minDepthBounds, float maxDepthBounds, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthBounds( m_commandBuffer, minDepthBounds, maxDepthBounds );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilCompareMask( VULKAN_HPP_NAMESPACE::StencilFaceFlags faceMask, uint32_t compareMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilCompareMask( m_commandBuffer, static_cast<VkStencilFaceFlags>( faceMask ), compareMask );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilWriteMask( VULKAN_HPP_NAMESPACE::StencilFaceFlags faceMask, uint32_t writeMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilWriteMask( m_commandBuffer, static_cast<VkStencilFaceFlags>( faceMask ), writeMask );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilReference( VULKAN_HPP_NAMESPACE::StencilFaceFlags faceMask, uint32_t reference, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilReference( m_commandBuffer, static_cast<VkStencilFaceFlags>( faceMask ), reference );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindDescriptorSets( VULKAN_HPP_NAMESPACE::PipelineBindPoint pipelineBindPoint, VULKAN_HPP_NAMESPACE::PipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VULKAN_HPP_NAMESPACE::DescriptorSet * pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t * pDynamicOffsets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindDescriptorSets( m_commandBuffer, static_cast<VkPipelineBindPoint>( pipelineBindPoint ), static_cast<VkPipelineLayout>( layout ), firstSet, descriptorSetCount, reinterpret_cast<const VkDescriptorSet *>( pDescriptorSets ), dynamicOffsetCount, pDynamicOffsets );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindDescriptorSets( VULKAN_HPP_NAMESPACE::PipelineBindPoint pipelineBindPoint, VULKAN_HPP_NAMESPACE::PipelineLayout layout, uint32_t firstSet, ArrayProxy<const VULKAN_HPP_NAMESPACE::DescriptorSet> const & descriptorSets, ArrayProxy<const uint32_t> const & dynamicOffsets, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBindDescriptorSets( m_commandBuffer, static_cast<VkPipelineBindPoint>( pipelineBindPoint ), static_cast<VkPipelineLayout>( layout ), firstSet, descriptorSets.size(), reinterpret_cast<const VkDescriptorSet *>( descriptorSets.data() ), dynamicOffsets.size(), dynamicOffsets.data() );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindIndexBuffer( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::IndexType indexType, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindIndexBuffer( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkIndexType>( indexType ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindVertexBuffers( uint32_t firstBinding, uint32_t bindingCount, const VULKAN_HPP_NAMESPACE::Buffer * pBuffers, const VULKAN_HPP_NAMESPACE::DeviceSize * pOffsets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindVertexBuffers( m_commandBuffer, firstBinding, bindingCount, reinterpret_cast<const VkBuffer *>( pBuffers ), reinterpret_cast<const VkDeviceSize *>( pOffsets ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindVertexBuffers( uint32_t firstBinding, ArrayProxy<const VULKAN_HPP_NAMESPACE::Buffer> const & buffers, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & offsets, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( buffers.size() == offsets.size() );
#else
    if ( buffers.size() != offsets.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers: buffers.size() != offsets.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBindVertexBuffers( m_commandBuffer, firstBinding, buffers.size(), reinterpret_cast<const VkBuffer *>( buffers.data() ), reinterpret_cast<const VkDeviceSize *>( offsets.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::draw( uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDraw( m_commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndexed( uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndexed( m_commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndirect( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, uint32_t drawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndirect( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), drawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndexedIndirect( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, uint32_t drawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndexedIndirect( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), drawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::dispatch( uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDispatch( m_commandBuffer, groupCountX, groupCountY, groupCountZ );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::dispatchIndirect( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDispatchIndirect( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBuffer( VULKAN_HPP_NAMESPACE::Buffer srcBuffer, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, uint32_t regionCount, const VULKAN_HPP_NAMESPACE::BufferCopy * pRegions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyBuffer( m_commandBuffer, static_cast<VkBuffer>( srcBuffer ), static_cast<VkBuffer>( dstBuffer ), regionCount, reinterpret_cast<const VkBufferCopy *>( pRegions ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBuffer( VULKAN_HPP_NAMESPACE::Buffer srcBuffer, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, ArrayProxy<const VULKAN_HPP_NAMESPACE::BufferCopy> const & regions, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyBuffer( m_commandBuffer, static_cast<VkBuffer>( srcBuffer ), static_cast<VkBuffer>( dstBuffer ), regions.size(), reinterpret_cast<const VkBufferCopy *>( regions.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImage( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, uint32_t regionCount, const VULKAN_HPP_NAMESPACE::ImageCopy * pRegions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyImage( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regionCount, reinterpret_cast<const VkImageCopy *>( pRegions ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImage( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageCopy> const & regions, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyImage( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regions.size(), reinterpret_cast<const VkImageCopy *>( regions.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::blitImage( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, uint32_t regionCount, const VULKAN_HPP_NAMESPACE::ImageBlit * pRegions, VULKAN_HPP_NAMESPACE::Filter filter, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBlitImage( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regionCount, reinterpret_cast<const VkImageBlit *>( pRegions ), static_cast<VkFilter>( filter ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::blitImage( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageBlit> const & regions, VULKAN_HPP_NAMESPACE::Filter filter, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBlitImage( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regions.size(), reinterpret_cast<const VkImageBlit *>( regions.data() ), static_cast<VkFilter>( filter ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBufferToImage( VULKAN_HPP_NAMESPACE::Buffer srcBuffer, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, uint32_t regionCount, const VULKAN_HPP_NAMESPACE::BufferImageCopy * pRegions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyBufferToImage( m_commandBuffer, static_cast<VkBuffer>( srcBuffer ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regionCount, reinterpret_cast<const VkBufferImageCopy *>( pRegions ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBufferToImage( VULKAN_HPP_NAMESPACE::Buffer srcBuffer, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, ArrayProxy<const VULKAN_HPP_NAMESPACE::BufferImageCopy> const & regions, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyBufferToImage( m_commandBuffer, static_cast<VkBuffer>( srcBuffer ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regions.size(), reinterpret_cast<const VkBufferImageCopy *>( regions.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImageToBuffer( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, uint32_t regionCount, const VULKAN_HPP_NAMESPACE::BufferImageCopy * pRegions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyImageToBuffer( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkBuffer>( dstBuffer ), regionCount, reinterpret_cast<const VkBufferImageCopy *>( pRegions ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImageToBuffer( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, ArrayProxy<const VULKAN_HPP_NAMESPACE::BufferImageCopy> const & regions, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyImageToBuffer( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkBuffer>( dstBuffer ), regions.size(), reinterpret_cast<const VkBufferImageCopy *>( regions.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::updateBuffer( VULKAN_HPP_NAMESPACE::Buffer dstBuffer, VULKAN_HPP_NAMESPACE::DeviceSize dstOffset, VULKAN_HPP_NAMESPACE::DeviceSize dataSize, const void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdUpdateBuffer( m_commandBuffer, static_cast<VkBuffer>( dstBuffer ), static_cast<VkDeviceSize>( dstOffset ), static_cast<VkDeviceSize>( dataSize ), pData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::updateBuffer( VULKAN_HPP_NAMESPACE::Buffer dstBuffer, VULKAN_HPP_NAMESPACE::DeviceSize dstOffset, ArrayProxy<const DataType> const & data, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdUpdateBuffer( m_commandBuffer, static_cast<VkBuffer>( dstBuffer ), static_cast<VkDeviceSize>( dstOffset ), data.size() * sizeof( DataType ), reinterpret_cast<const void *>( data.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::fillBuffer( VULKAN_HPP_NAMESPACE::Buffer dstBuffer, VULKAN_HPP_NAMESPACE::DeviceSize dstOffset, VULKAN_HPP_NAMESPACE::DeviceSize size, uint32_t data, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdFillBuffer( m_commandBuffer, static_cast<VkBuffer>( dstBuffer ), static_cast<VkDeviceSize>( dstOffset ), static_cast<VkDeviceSize>( size ), data );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::clearColorImage( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::ImageLayout imageLayout, const VULKAN_HPP_NAMESPACE::ClearColorValue * pColor, uint32_t rangeCount, const VULKAN_HPP_NAMESPACE::ImageSubresourceRange * pRanges, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdClearColorImage( m_commandBuffer, static_cast<VkImage>( image ), static_cast<VkImageLayout>( imageLayout ), reinterpret_cast<const VkClearColorValue *>( pColor ), rangeCount, reinterpret_cast<const VkImageSubresourceRange *>( pRanges ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::clearColorImage( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::ImageLayout imageLayout, const VULKAN_HPP_NAMESPACE::ClearColorValue & color, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageSubresourceRange> const & ranges, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdClearColorImage( m_commandBuffer, static_cast<VkImage>( image ), static_cast<VkImageLayout>( imageLayout ), reinterpret_cast<const VkClearColorValue *>( &color ), ranges.size(), reinterpret_cast<const VkImageSubresourceRange *>( ranges.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::clearDepthStencilImage( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::ImageLayout imageLayout, const VULKAN_HPP_NAMESPACE::ClearDepthStencilValue * pDepthStencil, uint32_t rangeCount, const VULKAN_HPP_NAMESPACE::ImageSubresourceRange * pRanges, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdClearDepthStencilImage( m_commandBuffer, static_cast<VkImage>( image ), static_cast<VkImageLayout>( imageLayout ), reinterpret_cast<const VkClearDepthStencilValue *>( pDepthStencil ), rangeCount, reinterpret_cast<const VkImageSubresourceRange *>( pRanges ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::clearDepthStencilImage( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::ImageLayout imageLayout, const VULKAN_HPP_NAMESPACE::ClearDepthStencilValue & depthStencil, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageSubresourceRange> const & ranges, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdClearDepthStencilImage( m_commandBuffer, static_cast<VkImage>( image ), static_cast<VkImageLayout>( imageLayout ), reinterpret_cast<const VkClearDepthStencilValue *>( &depthStencil ), ranges.size(), reinterpret_cast<const VkImageSubresourceRange *>( ranges.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::clearAttachments( uint32_t attachmentCount, const VULKAN_HPP_NAMESPACE::ClearAttachment * pAttachments, uint32_t rectCount, const VULKAN_HPP_NAMESPACE::ClearRect * pRects, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdClearAttachments( m_commandBuffer, attachmentCount, reinterpret_cast<const VkClearAttachment *>( pAttachments ), rectCount, reinterpret_cast<const VkClearRect *>( pRects ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::clearAttachments( ArrayProxy<const VULKAN_HPP_NAMESPACE::ClearAttachment> const & attachments, ArrayProxy<const VULKAN_HPP_NAMESPACE::ClearRect> const & rects, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdClearAttachments( m_commandBuffer, attachments.size(), reinterpret_cast<const VkClearAttachment *>( attachments.data() ), rects.size(), reinterpret_cast<const VkClearRect *>( rects.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resolveImage( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, uint32_t regionCount, const VULKAN_HPP_NAMESPACE::ImageResolve * pRegions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResolveImage( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regionCount, reinterpret_cast<const VkImageResolve *>( pRegions ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resolveImage( VULKAN_HPP_NAMESPACE::Image srcImage, VULKAN_HPP_NAMESPACE::ImageLayout srcImageLayout, VULKAN_HPP_NAMESPACE::Image dstImage, VULKAN_HPP_NAMESPACE::ImageLayout dstImageLayout, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageResolve> const & regions, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdResolveImage( m_commandBuffer, static_cast<VkImage>( srcImage ), static_cast<VkImageLayout>( srcImageLayout ), static_cast<VkImage>( dstImage ), static_cast<VkImageLayout>( dstImageLayout ), regions.size(), reinterpret_cast<const VkImageResolve *>( regions.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setEvent( VULKAN_HPP_NAMESPACE::Event event, VULKAN_HPP_NAMESPACE::PipelineStageFlags stageMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetEvent( m_commandBuffer, static_cast<VkEvent>( event ), static_cast<VkPipelineStageFlags>( stageMask ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resetEvent( VULKAN_HPP_NAMESPACE::Event event, VULKAN_HPP_NAMESPACE::PipelineStageFlags stageMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResetEvent( m_commandBuffer, static_cast<VkEvent>( event ), static_cast<VkPipelineStageFlags>( stageMask ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::waitEvents( uint32_t eventCount, const VULKAN_HPP_NAMESPACE::Event * pEvents, VULKAN_HPP_NAMESPACE::PipelineStageFlags srcStageMask, VULKAN_HPP_NAMESPACE::PipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VULKAN_HPP_NAMESPACE::MemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VULKAN_HPP_NAMESPACE::BufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VULKAN_HPP_NAMESPACE::ImageMemoryBarrier * pImageMemoryBarriers, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWaitEvents( m_commandBuffer, eventCount, reinterpret_cast<const VkEvent *>( pEvents ), static_cast<VkPipelineStageFlags>( srcStageMask ), static_cast<VkPipelineStageFlags>( dstStageMask ), memoryBarrierCount, reinterpret_cast<const VkMemoryBarrier *>( pMemoryBarriers ), bufferMemoryBarrierCount, reinterpret_cast<const VkBufferMemoryBarrier *>( pBufferMemoryBarriers ), imageMemoryBarrierCount, reinterpret_cast<const VkImageMemoryBarrier *>( pImageMemoryBarriers ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::waitEvents( ArrayProxy<const VULKAN_HPP_NAMESPACE::Event> const & events, VULKAN_HPP_NAMESPACE::PipelineStageFlags srcStageMask, VULKAN_HPP_NAMESPACE::PipelineStageFlags dstStageMask, ArrayProxy<const VULKAN_HPP_NAMESPACE::MemoryBarrier> const & memoryBarriers, ArrayProxy<const VULKAN_HPP_NAMESPACE::BufferMemoryBarrier> const & bufferMemoryBarriers, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageMemoryBarrier> const & imageMemoryBarriers, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdWaitEvents( m_commandBuffer, events.size(), reinterpret_cast<const VkEvent *>( events.data() ), static_cast<VkPipelineStageFlags>( srcStageMask ), static_cast<VkPipelineStageFlags>( dstStageMask ), memoryBarriers.size(), reinterpret_cast<const VkMemoryBarrier *>( memoryBarriers.data() ), bufferMemoryBarriers.size(), reinterpret_cast<const VkBufferMemoryBarrier *>( bufferMemoryBarriers.data() ), imageMemoryBarriers.size(), reinterpret_cast<const VkImageMemoryBarrier *>( imageMemoryBarriers.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pipelineBarrier( VULKAN_HPP_NAMESPACE::PipelineStageFlags srcStageMask, VULKAN_HPP_NAMESPACE::PipelineStageFlags dstStageMask, VULKAN_HPP_NAMESPACE::DependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VULKAN_HPP_NAMESPACE::MemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VULKAN_HPP_NAMESPACE::BufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VULKAN_HPP_NAMESPACE::ImageMemoryBarrier * pImageMemoryBarriers, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPipelineBarrier( m_commandBuffer, static_cast<VkPipelineStageFlags>( srcStageMask ), static_cast<VkPipelineStageFlags>( dstStageMask ), static_cast<VkDependencyFlags>( dependencyFlags ), memoryBarrierCount, reinterpret_cast<const VkMemoryBarrier *>( pMemoryBarriers ), bufferMemoryBarrierCount, reinterpret_cast<const VkBufferMemoryBarrier *>( pBufferMemoryBarriers ), imageMemoryBarrierCount, reinterpret_cast<const VkImageMemoryBarrier *>( pImageMemoryBarriers ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pipelineBarrier( VULKAN_HPP_NAMESPACE::PipelineStageFlags srcStageMask, VULKAN_HPP_NAMESPACE::PipelineStageFlags dstStageMask, VULKAN_HPP_NAMESPACE::DependencyFlags dependencyFlags, ArrayProxy<const VULKAN_HPP_NAMESPACE::MemoryBarrier> const & memoryBarriers, ArrayProxy<const VULKAN_HPP_NAMESPACE::BufferMemoryBarrier> const & bufferMemoryBarriers, ArrayProxy<const VULKAN_HPP_NAMESPACE::ImageMemoryBarrier> const & imageMemoryBarriers, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPipelineBarrier( m_commandBuffer, static_cast<VkPipelineStageFlags>( srcStageMask ), static_cast<VkPipelineStageFlags>( dstStageMask ), static_cast<VkDependencyFlags>( dependencyFlags ), memoryBarriers.size(), reinterpret_cast<const VkMemoryBarrier *>( memoryBarriers.data() ), bufferMemoryBarriers.size(), reinterpret_cast<const VkBufferMemoryBarrier *>( bufferMemoryBarriers.data() ), imageMemoryBarriers.size(), reinterpret_cast<const VkImageMemoryBarrier *>( imageMemoryBarriers.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginQuery( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, VULKAN_HPP_NAMESPACE::QueryControlFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginQuery( m_commandBuffer, static_cast<VkQueryPool>( queryPool ), query, static_cast<VkQueryControlFlags>( flags ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endQuery( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndQuery( m_commandBuffer, static_cast<VkQueryPool>( queryPool ), query );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resetQueryPool( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResetQueryPool( m_commandBuffer, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeTimestamp( VULKAN_HPP_NAMESPACE::PipelineStageFlagBits pipelineStage, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteTimestamp( m_commandBuffer, static_cast<VkPipelineStageFlagBits>( pipelineStage ), static_cast<VkQueryPool>( queryPool ), query );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyQueryPoolResults( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, VULKAN_HPP_NAMESPACE::DeviceSize dstOffset, VULKAN_HPP_NAMESPACE::DeviceSize stride, VULKAN_HPP_NAMESPACE::QueryResultFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyQueryPoolResults( m_commandBuffer, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount, static_cast<VkBuffer>( dstBuffer ), static_cast<VkDeviceSize>( dstOffset ), static_cast<VkDeviceSize>( stride ), static_cast<VkQueryResultFlags>( flags ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pushConstants( VULKAN_HPP_NAMESPACE::PipelineLayout layout, VULKAN_HPP_NAMESPACE::ShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void * pValues, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPushConstants( m_commandBuffer, static_cast<VkPipelineLayout>( layout ), static_cast<VkShaderStageFlags>( stageFlags ), offset, size, pValues );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename ValuesType, typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pushConstants( VULKAN_HPP_NAMESPACE::PipelineLayout layout, VULKAN_HPP_NAMESPACE::ShaderStageFlags stageFlags, uint32_t offset, ArrayProxy<const ValuesType> const & values, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPushConstants( m_commandBuffer, static_cast<VkPipelineLayout>( layout ), static_cast<VkShaderStageFlags>( stageFlags ), offset, values.size() * sizeof( ValuesType ), reinterpret_cast<const void *>( values.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderPass( const VULKAN_HPP_NAMESPACE::RenderPassBeginInfo * pRenderPassBegin, VULKAN_HPP_NAMESPACE::SubpassContents contents, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginRenderPass( m_commandBuffer, reinterpret_cast<const VkRenderPassBeginInfo *>( pRenderPassBegin ), static_cast<VkSubpassContents>( contents ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderPass( const VULKAN_HPP_NAMESPACE::RenderPassBeginInfo & renderPassBegin, VULKAN_HPP_NAMESPACE::SubpassContents contents, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginRenderPass( m_commandBuffer, reinterpret_cast<const VkRenderPassBeginInfo *>( &renderPassBegin ), static_cast<VkSubpassContents>( contents ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::nextSubpass( VULKAN_HPP_NAMESPACE::SubpassContents contents, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdNextSubpass( m_commandBuffer, static_cast<VkSubpassContents>( contents ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRenderPass( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndRenderPass( m_commandBuffer );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::executeCommands( uint32_t commandBufferCount, const VULKAN_HPP_NAMESPACE::CommandBuffer * pCommandBuffers, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdExecuteCommands( m_commandBuffer, commandBufferCount, reinterpret_cast<const VkCommandBuffer *>( pCommandBuffers ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::executeCommands( ArrayProxy<const VULKAN_HPP_NAMESPACE::CommandBuffer> const & commandBuffers, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdExecuteCommands( m_commandBuffer, commandBuffers.size(), reinterpret_cast<const VkCommandBuffer *>( commandBuffers.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_VERSION_1_1 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result enumerateInstanceVersion( uint32_t * pApiVersion, Dispatch const & d  ) VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumerateInstanceVersion( pApiVersion ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<uint32_t >::type enumerateInstanceVersion( Dispatch const & d )
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint32_t  apiVersion;
    Result result = static_cast<Result>( d.vkEnumerateInstanceVersion( &apiVersion ) );
    return createResultValue( result, apiVersion, VULKAN_HPP_NAMESPACE_STRING "::enumerateInstanceVersion" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindBufferMemory2( uint32_t bindInfoCount, const VULKAN_HPP_NAMESPACE::BindBufferMemoryInfo * pBindInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindBufferMemory2( m_device, bindInfoCount, reinterpret_cast<const VkBindBufferMemoryInfo *>( pBindInfos ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindBufferMemory2( ArrayProxy<const VULKAN_HPP_NAMESPACE::BindBufferMemoryInfo> const & bindInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindBufferMemory2( m_device, bindInfos.size(), reinterpret_cast<const VkBindBufferMemoryInfo *>( bindInfos.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindBufferMemory2" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindImageMemory2( uint32_t bindInfoCount, const VULKAN_HPP_NAMESPACE::BindImageMemoryInfo * pBindInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindImageMemory2( m_device, bindInfoCount, reinterpret_cast<const VkBindImageMemoryInfo *>( pBindInfos ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindImageMemory2( ArrayProxy<const VULKAN_HPP_NAMESPACE::BindImageMemoryInfo> const & bindInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindImageMemory2( m_device, bindInfos.size(), reinterpret_cast<const VkBindImageMemoryInfo *>( bindInfos.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindImageMemory2" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getGroupPeerMemoryFeatures( uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VULKAN_HPP_NAMESPACE::PeerMemoryFeatureFlags * pPeerMemoryFeatures, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceGroupPeerMemoryFeatures( m_device, heapIndex, localDeviceIndex, remoteDeviceIndex, reinterpret_cast<VkPeerMemoryFeatureFlags *>( pPeerMemoryFeatures ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PeerMemoryFeatureFlags  Device::getGroupPeerMemoryFeatures( uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PeerMemoryFeatureFlags  peerMemoryFeatures;
    d.vkGetDeviceGroupPeerMemoryFeatures( m_device, heapIndex, localDeviceIndex, remoteDeviceIndex, reinterpret_cast<VkPeerMemoryFeatureFlags *>( &peerMemoryFeatures ) );
    return peerMemoryFeatures;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDeviceMask( uint32_t deviceMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDeviceMask( m_commandBuffer, deviceMask );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::dispatchBase( uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDispatchBase( m_commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::enumeratePhysicalDeviceGroups( uint32_t * pPhysicalDeviceGroupCount, VULKAN_HPP_NAMESPACE::PhysicalDeviceGroupProperties * pPhysicalDeviceGroupProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumeratePhysicalDeviceGroups( m_instance, pPhysicalDeviceGroupCount, reinterpret_cast<VkPhysicalDeviceGroupProperties *>( pPhysicalDeviceGroupProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PhysicalDeviceGroupPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator>>::type Instance::enumeratePhysicalDeviceGroups( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator> physicalDeviceGroupProperties;
    uint32_t physicalDeviceGroupCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroups( m_instance, &physicalDeviceGroupCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && physicalDeviceGroupCount )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroups( m_instance, &physicalDeviceGroupCount, reinterpret_cast<VkPhysicalDeviceGroupProperties *>( physicalDeviceGroupProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( physicalDeviceGroupCount <= physicalDeviceGroupProperties.size() );
      if ( physicalDeviceGroupCount < physicalDeviceGroupProperties.size() )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
      }
    }
    return createResultValue( result, physicalDeviceGroupProperties, VULKAN_HPP_NAMESPACE_STRING"::Instance::enumeratePhysicalDeviceGroups" );
  }

  template <typename PhysicalDeviceGroupPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PhysicalDeviceGroupProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator>>::type Instance::enumeratePhysicalDeviceGroups( PhysicalDeviceGroupPropertiesAllocator & physicalDeviceGroupPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator> physicalDeviceGroupProperties( physicalDeviceGroupPropertiesAllocator );
    uint32_t physicalDeviceGroupCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroups( m_instance, &physicalDeviceGroupCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && physicalDeviceGroupCount )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroups( m_instance, &physicalDeviceGroupCount, reinterpret_cast<VkPhysicalDeviceGroupProperties *>( physicalDeviceGroupProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( physicalDeviceGroupCount <= physicalDeviceGroupProperties.size() );
      if ( physicalDeviceGroupCount < physicalDeviceGroupProperties.size() )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
      }
    }
    return createResultValue( result, physicalDeviceGroupProperties, VULKAN_HPP_NAMESPACE_STRING"::Instance::enumeratePhysicalDeviceGroups" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageMemoryRequirements2( const VULKAN_HPP_NAMESPACE::ImageMemoryRequirementsInfo2 * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageMemoryRequirements2( m_device, reinterpret_cast<const VkImageMemoryRequirementsInfo2 *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getImageMemoryRequirements2( const VULKAN_HPP_NAMESPACE::ImageMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetImageMemoryRequirements2( m_device, reinterpret_cast<const VkImageMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getImageMemoryRequirements2( const VULKAN_HPP_NAMESPACE::ImageMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetImageMemoryRequirements2( m_device, reinterpret_cast<const VkImageMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getBufferMemoryRequirements2( const VULKAN_HPP_NAMESPACE::BufferMemoryRequirementsInfo2 * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetBufferMemoryRequirements2( m_device, reinterpret_cast<const VkBufferMemoryRequirementsInfo2 *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getBufferMemoryRequirements2( const VULKAN_HPP_NAMESPACE::BufferMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetBufferMemoryRequirements2( m_device, reinterpret_cast<const VkBufferMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getBufferMemoryRequirements2( const VULKAN_HPP_NAMESPACE::BufferMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetBufferMemoryRequirements2( m_device, reinterpret_cast<const VkBufferMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageSparseMemoryRequirements2( const VULKAN_HPP_NAMESPACE::ImageSparseMemoryRequirementsInfo2 * pInfo, uint32_t * pSparseMemoryRequirementCount, VULKAN_HPP_NAMESPACE::SparseImageMemoryRequirements2 * pSparseMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageSparseMemoryRequirements2( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( pInfo ), pSparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( pSparseMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirements2( const VULKAN_HPP_NAMESPACE::ImageSparseMemoryRequirementsInfo2 & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements;
    uint32_t sparseMemoryRequirementCount;
    d.vkGetImageSparseMemoryRequirements2( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetImageSparseMemoryRequirements2( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }

  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageMemoryRequirements2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirements2( const VULKAN_HPP_NAMESPACE::ImageSparseMemoryRequirementsInfo2 & info, SparseImageMemoryRequirements2Allocator & sparseImageMemoryRequirements2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements( sparseImageMemoryRequirements2Allocator );
    uint32_t sparseMemoryRequirementCount;
    d.vkGetImageSparseMemoryRequirements2( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetImageSparseMemoryRequirements2( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getFeatures2( VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2 * pFeatures, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceFeatures2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures2 *>( pFeatures ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2  PhysicalDevice::getFeatures2( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2  features;
    d.vkGetPhysicalDeviceFeatures2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures2 *>( &features ) );
    return features;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getFeatures2( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2 & features = structureChain.template get<VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2>();
    d.vkGetPhysicalDeviceFeatures2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures2 *>( &features ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getProperties2( VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2 * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceProperties2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties2 *>( pProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2  PhysicalDevice::getProperties2( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2  properties;
    d.vkGetPhysicalDeviceProperties2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties2 *>( &properties ) );
    return properties;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getProperties2( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2 & properties = structureChain.template get<VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2>();
    d.vkGetPhysicalDeviceProperties2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties2 *>( &properties ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getFormatProperties2( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::FormatProperties2 * pFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceFormatProperties2( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties2 *>( pFormatProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::FormatProperties2  PhysicalDevice::getFormatProperties2( VULKAN_HPP_NAMESPACE::Format format, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::FormatProperties2  formatProperties;
    d.vkGetPhysicalDeviceFormatProperties2( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties2 *>( &formatProperties ) );
    return formatProperties;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getFormatProperties2( VULKAN_HPP_NAMESPACE::Format format, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::FormatProperties2 & formatProperties = structureChain.template get<VULKAN_HPP_NAMESPACE::FormatProperties2>();
    d.vkGetPhysicalDeviceFormatProperties2( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties2 *>( &formatProperties ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getImageFormatProperties2( const VULKAN_HPP_NAMESPACE::PhysicalDeviceImageFormatInfo2 * pImageFormatInfo, VULKAN_HPP_NAMESPACE::ImageFormatProperties2 * pImageFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2 *>( pImageFormatInfo ), reinterpret_cast<VkImageFormatProperties2 *>( pImageFormatProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ImageFormatProperties2 >::type PhysicalDevice::getImageFormatProperties2( const VULKAN_HPP_NAMESPACE::PhysicalDeviceImageFormatInfo2 & imageFormatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ImageFormatProperties2  imageFormatProperties;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2 *>( &imageFormatInfo ), reinterpret_cast<VkImageFormatProperties2 *>( &imageFormatProperties ) ) );
    return createResultValue( result, imageFormatProperties, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getImageFormatProperties2" );
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<StructureChain<X, Y, Z...>>::type PhysicalDevice::getImageFormatProperties2( const VULKAN_HPP_NAMESPACE::PhysicalDeviceImageFormatInfo2 & imageFormatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::ImageFormatProperties2 & imageFormatProperties = structureChain.template get<VULKAN_HPP_NAMESPACE::ImageFormatProperties2>();
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2 *>( &imageFormatInfo ), reinterpret_cast<VkImageFormatProperties2 *>( &imageFormatProperties ) ) );
    return createResultValue( result, structureChain, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getImageFormatProperties2" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getQueueFamilyProperties2( uint32_t * pQueueFamilyPropertyCount, VULKAN_HPP_NAMESPACE::QueueFamilyProperties2 * pQueueFamilyProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, pQueueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( pQueueFamilyProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename QueueFamilyProperties2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> PhysicalDevice::getQueueFamilyProperties2( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> queueFamilyProperties;
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    queueFamilyProperties.resize( queueFamilyPropertyCount );
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    return queueFamilyProperties;
  }

  template <typename QueueFamilyProperties2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, QueueFamilyProperties2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> PhysicalDevice::getQueueFamilyProperties2( QueueFamilyProperties2Allocator & queueFamilyProperties2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> queueFamilyProperties( queueFamilyProperties2Allocator );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    queueFamilyProperties.resize( queueFamilyPropertyCount );
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    return queueFamilyProperties;
  }

  template <typename StructureChain, typename StructureChainAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<StructureChain, StructureChainAllocator> PhysicalDevice::getQueueFamilyProperties2( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    std::vector<StructureChain, StructureChainAllocator> returnVector( queueFamilyPropertyCount );
    std::vector<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2> queueFamilyProperties( queueFamilyPropertyCount );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      queueFamilyProperties[i].pNext =
        returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>().pNext;
    }
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>() = queueFamilyProperties[i];
    }
    return returnVector;
  }

  template <typename StructureChain, typename StructureChainAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, StructureChain>::value, int>::type>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<StructureChain, StructureChainAllocator> PhysicalDevice::getQueueFamilyProperties2( StructureChainAllocator & structureChainAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    std::vector<StructureChain, StructureChainAllocator> returnVector( queueFamilyPropertyCount, structureChainAllocator );
    std::vector<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2> queueFamilyProperties( queueFamilyPropertyCount );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      queueFamilyProperties[i].pNext =
        returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>().pNext;
    }
    d.vkGetPhysicalDeviceQueueFamilyProperties2( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>() = queueFamilyProperties[i];
    }
    return returnVector;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getMemoryProperties2( VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2 * pMemoryProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceMemoryProperties2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties2 *>( pMemoryProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2  PhysicalDevice::getMemoryProperties2( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2  memoryProperties;
    d.vkGetPhysicalDeviceMemoryProperties2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties2 *>( &memoryProperties ) );
    return memoryProperties;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getMemoryProperties2( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2 & memoryProperties = structureChain.template get<VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2>();
    d.vkGetPhysicalDeviceMemoryProperties2( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties2 *>( &memoryProperties ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getSparseImageFormatProperties2( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSparseImageFormatInfo2 * pFormatInfo, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::SparseImageFormatProperties2 * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceSparseImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( pFormatInfo ), pPropertyCount, reinterpret_cast<VkSparseImageFormatProperties2 *>( pProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageFormatProperties2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> PhysicalDevice::getSparseImageFormatProperties2( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSparseImageFormatInfo2 & formatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> properties;
    uint32_t propertyCount;
    d.vkGetPhysicalDeviceSparseImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, nullptr );
    properties.resize( propertyCount );
    d.vkGetPhysicalDeviceSparseImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, reinterpret_cast<VkSparseImageFormatProperties2 *>( properties.data() ) );
    VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
    return properties;
  }

  template <typename SparseImageFormatProperties2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageFormatProperties2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> PhysicalDevice::getSparseImageFormatProperties2( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSparseImageFormatInfo2 & formatInfo, SparseImageFormatProperties2Allocator & sparseImageFormatProperties2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> properties( sparseImageFormatProperties2Allocator );
    uint32_t propertyCount;
    d.vkGetPhysicalDeviceSparseImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, nullptr );
    properties.resize( propertyCount );
    d.vkGetPhysicalDeviceSparseImageFormatProperties2( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, reinterpret_cast<VkSparseImageFormatProperties2 *>( properties.data() ) );
    VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
    return properties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::trimCommandPool( VULKAN_HPP_NAMESPACE::CommandPool commandPool, VULKAN_HPP_NAMESPACE::CommandPoolTrimFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkTrimCommandPool( m_device, static_cast<VkCommandPool>( commandPool ), static_cast<VkCommandPoolTrimFlags>( flags ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getQueue2( const VULKAN_HPP_NAMESPACE::DeviceQueueInfo2 * pQueueInfo, VULKAN_HPP_NAMESPACE::Queue * pQueue, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceQueue2( m_device, reinterpret_cast<const VkDeviceQueueInfo2 *>( pQueueInfo ), reinterpret_cast<VkQueue *>( pQueue ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::Queue  Device::getQueue2( const VULKAN_HPP_NAMESPACE::DeviceQueueInfo2 & queueInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Queue  queue;
    d.vkGetDeviceQueue2( m_device, reinterpret_cast<const VkDeviceQueueInfo2 *>( &queueInfo ), reinterpret_cast<VkQueue *>( &queue ) );
    return queue;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createSamplerYcbcrConversion( const VULKAN_HPP_NAMESPACE::SamplerYcbcrConversionCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion * pYcbcrConversion, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateSamplerYcbcrConversion( m_device, reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSamplerYcbcrConversion *>( pYcbcrConversion ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion >::type Device::createSamplerYcbcrConversion( const VULKAN_HPP_NAMESPACE::SamplerYcbcrConversionCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion  ycbcrConversion;
    Result result = static_cast<Result>( d.vkCreateSamplerYcbcrConversion( m_device, reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSamplerYcbcrConversion *>( &ycbcrConversion ) ) );
    return createResultValue( result, ycbcrConversion, VULKAN_HPP_NAMESPACE_STRING "::Device::createSamplerYcbcrConversion" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion, Dispatch>>::type Device::createSamplerYcbcrConversionUnique( const VULKAN_HPP_NAMESPACE::SamplerYcbcrConversionCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion;
    Result result = static_cast<Result>( d.vkCreateSamplerYcbcrConversion( m_device, reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSamplerYcbcrConversion *>( &ycbcrConversion ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion, Dispatch>( result, ycbcrConversion, VULKAN_HPP_NAMESPACE_STRING "::Device::createSamplerYcbcrConversionUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySamplerYcbcrConversion( VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySamplerYcbcrConversion( m_device, static_cast<VkSamplerYcbcrConversion>( ycbcrConversion ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySamplerYcbcrConversion( VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySamplerYcbcrConversion( m_device, static_cast<VkSamplerYcbcrConversion>( ycbcrConversion ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySamplerYcbcrConversion( m_device, static_cast<VkSamplerYcbcrConversion>( ycbcrConversion ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySamplerYcbcrConversion( m_device, static_cast<VkSamplerYcbcrConversion>( ycbcrConversion ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createDescriptorUpdateTemplate( const VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplateCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate * pDescriptorUpdateTemplate, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDescriptorUpdateTemplate( m_device, reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDescriptorUpdateTemplate *>( pDescriptorUpdateTemplate ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate >::type Device::createDescriptorUpdateTemplate( const VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplateCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate  descriptorUpdateTemplate;
    Result result = static_cast<Result>( d.vkCreateDescriptorUpdateTemplate( m_device, reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorUpdateTemplate *>( &descriptorUpdateTemplate ) ) );
    return createResultValue( result, descriptorUpdateTemplate, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorUpdateTemplate" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate, Dispatch>>::type Device::createDescriptorUpdateTemplateUnique( const VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplateCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate;
    Result result = static_cast<Result>( d.vkCreateDescriptorUpdateTemplate( m_device, reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorUpdateTemplate *>( &descriptorUpdateTemplate ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate, Dispatch>( result, descriptorUpdateTemplate, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorUpdateTemplateUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorUpdateTemplate( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorUpdateTemplate( m_device, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorUpdateTemplate( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorUpdateTemplate( m_device, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorUpdateTemplate( m_device, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorUpdateTemplate( m_device, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::updateDescriptorSetWithTemplate( VULKAN_HPP_NAMESPACE::DescriptorSet descriptorSet, VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, const void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkUpdateDescriptorSetWithTemplate( m_device, static_cast<VkDescriptorSet>( descriptorSet ), static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), pData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Dispatch>
  VULKAN_HPP_INLINE void Device::updateDescriptorSetWithTemplate( VULKAN_HPP_NAMESPACE::DescriptorSet descriptorSet, VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, DataType const & data, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkUpdateDescriptorSetWithTemplate( m_device, static_cast<VkDescriptorSet>( descriptorSet ), static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const void *>( &data ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getExternalBufferProperties( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalBufferInfo * pExternalBufferInfo, VULKAN_HPP_NAMESPACE::ExternalBufferProperties * pExternalBufferProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceExternalBufferProperties( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo *>( pExternalBufferInfo ), reinterpret_cast<VkExternalBufferProperties *>( pExternalBufferProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::ExternalBufferProperties  PhysicalDevice::getExternalBufferProperties( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalBufferInfo & externalBufferInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalBufferProperties  externalBufferProperties;
    d.vkGetPhysicalDeviceExternalBufferProperties( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo *>( &externalBufferInfo ), reinterpret_cast<VkExternalBufferProperties *>( &externalBufferProperties ) );
    return externalBufferProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getExternalFenceProperties( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalFenceInfo * pExternalFenceInfo, VULKAN_HPP_NAMESPACE::ExternalFenceProperties * pExternalFenceProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceExternalFenceProperties( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo *>( pExternalFenceInfo ), reinterpret_cast<VkExternalFenceProperties *>( pExternalFenceProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::ExternalFenceProperties  PhysicalDevice::getExternalFenceProperties( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalFenceInfo & externalFenceInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalFenceProperties  externalFenceProperties;
    d.vkGetPhysicalDeviceExternalFenceProperties( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo *>( &externalFenceInfo ), reinterpret_cast<VkExternalFenceProperties *>( &externalFenceProperties ) );
    return externalFenceProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getExternalSemaphoreProperties( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo, VULKAN_HPP_NAMESPACE::ExternalSemaphoreProperties * pExternalSemaphoreProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceExternalSemaphoreProperties( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo *>( pExternalSemaphoreInfo ), reinterpret_cast<VkExternalSemaphoreProperties *>( pExternalSemaphoreProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::ExternalSemaphoreProperties  PhysicalDevice::getExternalSemaphoreProperties( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalSemaphoreInfo & externalSemaphoreInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalSemaphoreProperties  externalSemaphoreProperties;
    d.vkGetPhysicalDeviceExternalSemaphoreProperties( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo *>( &externalSemaphoreInfo ), reinterpret_cast<VkExternalSemaphoreProperties *>( &externalSemaphoreProperties ) );
    return externalSemaphoreProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getDescriptorSetLayoutSupport( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo * pCreateInfo, VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport * pSupport, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDescriptorSetLayoutSupport( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( pCreateInfo ), reinterpret_cast<VkDescriptorSetLayoutSupport *>( pSupport ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport  Device::getDescriptorSetLayoutSupport( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo & createInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport  support;
    d.vkGetDescriptorSetLayoutSupport( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( &createInfo ), reinterpret_cast<VkDescriptorSetLayoutSupport *>( &support ) );
    return support;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getDescriptorSetLayoutSupport( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo & createInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport & support = structureChain.template get<VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport>();
    d.vkGetDescriptorSetLayoutSupport( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( &createInfo ), reinterpret_cast<VkDescriptorSetLayoutSupport *>( &support ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_VERSION_1_2 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndirectCount( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndirectCount( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndexedIndirectCount( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndexedIndirectCount( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createRenderPass2( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo2 * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::RenderPass * pRenderPass, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateRenderPass2( m_device, reinterpret_cast<const VkRenderPassCreateInfo2 *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkRenderPass *>( pRenderPass ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::RenderPass >::type Device::createRenderPass2( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo2 & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::RenderPass  renderPass;
    Result result = static_cast<Result>( d.vkCreateRenderPass2( m_device, reinterpret_cast<const VkRenderPassCreateInfo2 *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkRenderPass *>( &renderPass ) ) );
    return createResultValue( result, renderPass, VULKAN_HPP_NAMESPACE_STRING "::Device::createRenderPass2" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::RenderPass, Dispatch>>::type Device::createRenderPass2Unique( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo2 & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::RenderPass renderPass;
    Result result = static_cast<Result>( d.vkCreateRenderPass2( m_device, reinterpret_cast<const VkRenderPassCreateInfo2 *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkRenderPass *>( &renderPass ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::RenderPass, Dispatch>( result, renderPass, VULKAN_HPP_NAMESPACE_STRING "::Device::createRenderPass2Unique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderPass2( const VULKAN_HPP_NAMESPACE::RenderPassBeginInfo * pRenderPassBegin, const VULKAN_HPP_NAMESPACE::SubpassBeginInfo * pSubpassBeginInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginRenderPass2( m_commandBuffer, reinterpret_cast<const VkRenderPassBeginInfo *>( pRenderPassBegin ), reinterpret_cast<const VkSubpassBeginInfo *>( pSubpassBeginInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderPass2( const VULKAN_HPP_NAMESPACE::RenderPassBeginInfo & renderPassBegin, const VULKAN_HPP_NAMESPACE::SubpassBeginInfo & subpassBeginInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginRenderPass2( m_commandBuffer, reinterpret_cast<const VkRenderPassBeginInfo *>( &renderPassBegin ), reinterpret_cast<const VkSubpassBeginInfo *>( &subpassBeginInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::nextSubpass2( const VULKAN_HPP_NAMESPACE::SubpassBeginInfo * pSubpassBeginInfo, const VULKAN_HPP_NAMESPACE::SubpassEndInfo * pSubpassEndInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdNextSubpass2( m_commandBuffer, reinterpret_cast<const VkSubpassBeginInfo *>( pSubpassBeginInfo ), reinterpret_cast<const VkSubpassEndInfo *>( pSubpassEndInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::nextSubpass2( const VULKAN_HPP_NAMESPACE::SubpassBeginInfo & subpassBeginInfo, const VULKAN_HPP_NAMESPACE::SubpassEndInfo & subpassEndInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdNextSubpass2( m_commandBuffer, reinterpret_cast<const VkSubpassBeginInfo *>( &subpassBeginInfo ), reinterpret_cast<const VkSubpassEndInfo *>( &subpassEndInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRenderPass2( const VULKAN_HPP_NAMESPACE::SubpassEndInfo * pSubpassEndInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndRenderPass2( m_commandBuffer, reinterpret_cast<const VkSubpassEndInfo *>( pSubpassEndInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRenderPass2( const VULKAN_HPP_NAMESPACE::SubpassEndInfo & subpassEndInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdEndRenderPass2( m_commandBuffer, reinterpret_cast<const VkSubpassEndInfo *>( &subpassEndInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::resetQueryPool( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkResetQueryPool( m_device, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSemaphoreCounterValue( VULKAN_HPP_NAMESPACE::Semaphore semaphore, uint64_t * pValue, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSemaphoreCounterValue( m_device, static_cast<VkSemaphore>( semaphore ), pValue ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<uint64_t >::type Device::getSemaphoreCounterValue( VULKAN_HPP_NAMESPACE::Semaphore semaphore, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint64_t  value;
    Result result = static_cast<Result>( d.vkGetSemaphoreCounterValue( m_device, static_cast<VkSemaphore>( semaphore ), &value ) );
    return createResultValue( result, value, VULKAN_HPP_NAMESPACE_STRING "::Device::getSemaphoreCounterValue" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitSemaphores( const VULKAN_HPP_NAMESPACE::SemaphoreWaitInfo * pWaitInfo, uint64_t timeout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkWaitSemaphores( m_device, reinterpret_cast<const VkSemaphoreWaitInfo *>( pWaitInfo ), timeout ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitSemaphores( const VULKAN_HPP_NAMESPACE::SemaphoreWaitInfo & waitInfo, uint64_t timeout, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkWaitSemaphores( m_device, reinterpret_cast<const VkSemaphoreWaitInfo *>( &waitInfo ), timeout ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::waitSemaphores", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eTimeout } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::signalSemaphore( const VULKAN_HPP_NAMESPACE::SemaphoreSignalInfo * pSignalInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSignalSemaphore( m_device, reinterpret_cast<const VkSemaphoreSignalInfo *>( pSignalInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::signalSemaphore( const VULKAN_HPP_NAMESPACE::SemaphoreSignalInfo & signalInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSignalSemaphore( m_device, reinterpret_cast<const VkSemaphoreSignalInfo *>( &signalInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::signalSemaphore" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getBufferAddress( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<DeviceAddress>( d.vkGetBufferDeviceAddress( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getBufferAddress( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetBufferDeviceAddress( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getBufferOpaqueCaptureAddress( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetBufferOpaqueCaptureAddress( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getBufferOpaqueCaptureAddress( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetBufferOpaqueCaptureAddress( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getMemoryOpaqueCaptureAddress( const VULKAN_HPP_NAMESPACE::DeviceMemoryOpaqueCaptureAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetDeviceMemoryOpaqueCaptureAddress( m_device, reinterpret_cast<const VkDeviceMemoryOpaqueCaptureAddressInfo *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getMemoryOpaqueCaptureAddress( const VULKAN_HPP_NAMESPACE::DeviceMemoryOpaqueCaptureAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetDeviceMemoryOpaqueCaptureAddress( m_device, reinterpret_cast<const VkDeviceMemoryOpaqueCaptureAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_VERSION_1_3 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getToolProperties( uint32_t * pToolCount, VULKAN_HPP_NAMESPACE::PhysicalDeviceToolProperties * pToolProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceToolProperties( m_physicalDevice, pToolCount, reinterpret_cast<VkPhysicalDeviceToolProperties *>( pToolProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PhysicalDeviceToolPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator>>::type PhysicalDevice::getToolProperties( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator> toolProperties;
    uint32_t toolCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceToolProperties( m_physicalDevice, &toolCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && toolCount )
      {
        toolProperties.resize( toolCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceToolProperties( m_physicalDevice, &toolCount, reinterpret_cast<VkPhysicalDeviceToolProperties *>( toolProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( toolCount <= toolProperties.size() );
      if ( toolCount < toolProperties.size() )
      {
        toolProperties.resize( toolCount );
      }
    }
    return createResultValue( result, toolProperties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getToolProperties" );
  }

  template <typename PhysicalDeviceToolPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PhysicalDeviceToolProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator>>::type PhysicalDevice::getToolProperties( PhysicalDeviceToolPropertiesAllocator & physicalDeviceToolPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator> toolProperties( physicalDeviceToolPropertiesAllocator );
    uint32_t toolCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceToolProperties( m_physicalDevice, &toolCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && toolCount )
      {
        toolProperties.resize( toolCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceToolProperties( m_physicalDevice, &toolCount, reinterpret_cast<VkPhysicalDeviceToolProperties *>( toolProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( toolCount <= toolProperties.size() );
      if ( toolCount < toolProperties.size() )
      {
        toolProperties.resize( toolCount );
      }
    }
    return createResultValue( result, toolProperties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getToolProperties" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createPrivateDataSlot( const VULKAN_HPP_NAMESPACE::PrivateDataSlotCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::PrivateDataSlot * pPrivateDataSlot, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreatePrivateDataSlot( m_device, reinterpret_cast<const VkPrivateDataSlotCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPrivateDataSlot *>( pPrivateDataSlot ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::PrivateDataSlot >::type Device::createPrivateDataSlot( const VULKAN_HPP_NAMESPACE::PrivateDataSlotCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PrivateDataSlot  privateDataSlot;
    Result result = static_cast<Result>( d.vkCreatePrivateDataSlot( m_device, reinterpret_cast<const VkPrivateDataSlotCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPrivateDataSlot *>( &privateDataSlot ) ) );
    return createResultValue( result, privateDataSlot, VULKAN_HPP_NAMESPACE_STRING "::Device::createPrivateDataSlot" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::PrivateDataSlot, Dispatch>>::type Device::createPrivateDataSlotUnique( const VULKAN_HPP_NAMESPACE::PrivateDataSlotCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot;
    Result result = static_cast<Result>( d.vkCreatePrivateDataSlot( m_device, reinterpret_cast<const VkPrivateDataSlotCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPrivateDataSlot *>( &privateDataSlot ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::PrivateDataSlot, Dispatch>( result, privateDataSlot, VULKAN_HPP_NAMESPACE_STRING "::Device::createPrivateDataSlotUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPrivateDataSlot( VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPrivateDataSlot( m_device, static_cast<VkPrivateDataSlot>( privateDataSlot ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPrivateDataSlot( VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPrivateDataSlot( m_device, static_cast<VkPrivateDataSlot>( privateDataSlot ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPrivateDataSlot( m_device, static_cast<VkPrivateDataSlot>( privateDataSlot ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPrivateDataSlot( m_device, static_cast<VkPrivateDataSlot>( privateDataSlot ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setPrivateData( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, uint64_t data, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetPrivateData( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), data ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setPrivateData( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, uint64_t data, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetPrivateData( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), data ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setPrivateData" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getPrivateData( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, uint64_t * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPrivateData( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), pData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE uint64_t  Device::getPrivateData( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint64_t  data;
    d.vkGetPrivateData( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), &data );
    return data;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setEvent2( VULKAN_HPP_NAMESPACE::Event event, const VULKAN_HPP_NAMESPACE::DependencyInfo * pDependencyInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetEvent2( m_commandBuffer, static_cast<VkEvent>( event ), reinterpret_cast<const VkDependencyInfo *>( pDependencyInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setEvent2( VULKAN_HPP_NAMESPACE::Event event, const VULKAN_HPP_NAMESPACE::DependencyInfo & dependencyInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetEvent2( m_commandBuffer, static_cast<VkEvent>( event ), reinterpret_cast<const VkDependencyInfo *>( &dependencyInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resetEvent2( VULKAN_HPP_NAMESPACE::Event event, VULKAN_HPP_NAMESPACE::PipelineStageFlags2 stageMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResetEvent2( m_commandBuffer, static_cast<VkEvent>( event ), static_cast<VkPipelineStageFlags2>( stageMask ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::waitEvents2( uint32_t eventCount, const VULKAN_HPP_NAMESPACE::Event * pEvents, const VULKAN_HPP_NAMESPACE::DependencyInfo * pDependencyInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWaitEvents2( m_commandBuffer, eventCount, reinterpret_cast<const VkEvent *>( pEvents ), reinterpret_cast<const VkDependencyInfo *>( pDependencyInfos ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::waitEvents2( ArrayProxy<const VULKAN_HPP_NAMESPACE::Event> const & events, ArrayProxy<const VULKAN_HPP_NAMESPACE::DependencyInfo> const & dependencyInfos, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( events.size() == dependencyInfos.size() );
#else
    if ( events.size() != dependencyInfos.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::waitEvents2: events.size() != dependencyInfos.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdWaitEvents2( m_commandBuffer, events.size(), reinterpret_cast<const VkEvent *>( events.data() ), reinterpret_cast<const VkDependencyInfo *>( dependencyInfos.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pipelineBarrier2( const VULKAN_HPP_NAMESPACE::DependencyInfo * pDependencyInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPipelineBarrier2( m_commandBuffer, reinterpret_cast<const VkDependencyInfo *>( pDependencyInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pipelineBarrier2( const VULKAN_HPP_NAMESPACE::DependencyInfo & dependencyInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPipelineBarrier2( m_commandBuffer, reinterpret_cast<const VkDependencyInfo *>( &dependencyInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeTimestamp2( VULKAN_HPP_NAMESPACE::PipelineStageFlags2 stage, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteTimestamp2( m_commandBuffer, static_cast<VkPipelineStageFlags2>( stage ), static_cast<VkQueryPool>( queryPool ), query );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::submit2( uint32_t submitCount, const VULKAN_HPP_NAMESPACE::SubmitInfo2 * pSubmits, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueueSubmit2( m_queue, submitCount, reinterpret_cast<const VkSubmitInfo2 *>( pSubmits ), static_cast<VkFence>( fence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Queue::submit2( ArrayProxy<const VULKAN_HPP_NAMESPACE::SubmitInfo2> const & submits, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueueSubmit2( m_queue, submits.size(), reinterpret_cast<const VkSubmitInfo2 *>( submits.data() ), static_cast<VkFence>( fence ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::submit2" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBuffer2( const VULKAN_HPP_NAMESPACE::CopyBufferInfo2 * pCopyBufferInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyBuffer2( m_commandBuffer, reinterpret_cast<const VkCopyBufferInfo2 *>( pCopyBufferInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBuffer2( const VULKAN_HPP_NAMESPACE::CopyBufferInfo2 & copyBufferInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyBuffer2( m_commandBuffer, reinterpret_cast<const VkCopyBufferInfo2 *>( &copyBufferInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImage2( const VULKAN_HPP_NAMESPACE::CopyImageInfo2 * pCopyImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyImage2( m_commandBuffer, reinterpret_cast<const VkCopyImageInfo2 *>( pCopyImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImage2( const VULKAN_HPP_NAMESPACE::CopyImageInfo2 & copyImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyImage2( m_commandBuffer, reinterpret_cast<const VkCopyImageInfo2 *>( &copyImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBufferToImage2( const VULKAN_HPP_NAMESPACE::CopyBufferToImageInfo2 * pCopyBufferToImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyBufferToImage2( m_commandBuffer, reinterpret_cast<const VkCopyBufferToImageInfo2 *>( pCopyBufferToImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBufferToImage2( const VULKAN_HPP_NAMESPACE::CopyBufferToImageInfo2 & copyBufferToImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyBufferToImage2( m_commandBuffer, reinterpret_cast<const VkCopyBufferToImageInfo2 *>( &copyBufferToImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImageToBuffer2( const VULKAN_HPP_NAMESPACE::CopyImageToBufferInfo2 * pCopyImageToBufferInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyImageToBuffer2( m_commandBuffer, reinterpret_cast<const VkCopyImageToBufferInfo2 *>( pCopyImageToBufferInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImageToBuffer2( const VULKAN_HPP_NAMESPACE::CopyImageToBufferInfo2 & copyImageToBufferInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyImageToBuffer2( m_commandBuffer, reinterpret_cast<const VkCopyImageToBufferInfo2 *>( &copyImageToBufferInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::blitImage2( const VULKAN_HPP_NAMESPACE::BlitImageInfo2 * pBlitImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBlitImage2( m_commandBuffer, reinterpret_cast<const VkBlitImageInfo2 *>( pBlitImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::blitImage2( const VULKAN_HPP_NAMESPACE::BlitImageInfo2 & blitImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBlitImage2( m_commandBuffer, reinterpret_cast<const VkBlitImageInfo2 *>( &blitImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resolveImage2( const VULKAN_HPP_NAMESPACE::ResolveImageInfo2 * pResolveImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResolveImage2( m_commandBuffer, reinterpret_cast<const VkResolveImageInfo2 *>( pResolveImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resolveImage2( const VULKAN_HPP_NAMESPACE::ResolveImageInfo2 & resolveImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdResolveImage2( m_commandBuffer, reinterpret_cast<const VkResolveImageInfo2 *>( &resolveImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRendering( const VULKAN_HPP_NAMESPACE::RenderingInfo * pRenderingInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginRendering( m_commandBuffer, reinterpret_cast<const VkRenderingInfo *>( pRenderingInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRendering( const VULKAN_HPP_NAMESPACE::RenderingInfo & renderingInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginRendering( m_commandBuffer, reinterpret_cast<const VkRenderingInfo *>( &renderingInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRendering( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndRendering( m_commandBuffer );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setCullMode( VULKAN_HPP_NAMESPACE::CullModeFlags cullMode, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetCullMode( m_commandBuffer, static_cast<VkCullModeFlags>( cullMode ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setFrontFace( VULKAN_HPP_NAMESPACE::FrontFace frontFace, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetFrontFace( m_commandBuffer, static_cast<VkFrontFace>( frontFace ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setPrimitiveTopology( VULKAN_HPP_NAMESPACE::PrimitiveTopology primitiveTopology, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetPrimitiveTopology( m_commandBuffer, static_cast<VkPrimitiveTopology>( primitiveTopology ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportWithCount( uint32_t viewportCount, const VULKAN_HPP_NAMESPACE::Viewport * pViewports, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetViewportWithCount( m_commandBuffer, viewportCount, reinterpret_cast<const VkViewport *>( pViewports ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportWithCount( ArrayProxy<const VULKAN_HPP_NAMESPACE::Viewport> const & viewports, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetViewportWithCount( m_commandBuffer, viewports.size(), reinterpret_cast<const VkViewport *>( viewports.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setScissorWithCount( uint32_t scissorCount, const VULKAN_HPP_NAMESPACE::Rect2D * pScissors, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetScissorWithCount( m_commandBuffer, scissorCount, reinterpret_cast<const VkRect2D *>( pScissors ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setScissorWithCount( ArrayProxy<const VULKAN_HPP_NAMESPACE::Rect2D> const & scissors, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetScissorWithCount( m_commandBuffer, scissors.size(), reinterpret_cast<const VkRect2D *>( scissors.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindVertexBuffers2( uint32_t firstBinding, uint32_t bindingCount, const VULKAN_HPP_NAMESPACE::Buffer * pBuffers, const VULKAN_HPP_NAMESPACE::DeviceSize * pOffsets, const VULKAN_HPP_NAMESPACE::DeviceSize * pSizes, const VULKAN_HPP_NAMESPACE::DeviceSize * pStrides, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindVertexBuffers2( m_commandBuffer, firstBinding, bindingCount, reinterpret_cast<const VkBuffer *>( pBuffers ), reinterpret_cast<const VkDeviceSize *>( pOffsets ), reinterpret_cast<const VkDeviceSize *>( pSizes ), reinterpret_cast<const VkDeviceSize *>( pStrides ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindVertexBuffers2( uint32_t firstBinding, ArrayProxy<const VULKAN_HPP_NAMESPACE::Buffer> const & buffers, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & offsets, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & sizes, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & strides, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( buffers.size() == offsets.size() );
    VULKAN_HPP_ASSERT( sizes.empty() || buffers.size() == sizes.size() );
    VULKAN_HPP_ASSERT( strides.empty() || buffers.size() == strides.size() );
#else
    if ( buffers.size() != offsets.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers2: buffers.size() != offsets.size()" );
  }
    if ( !sizes.empty() && buffers.size() != sizes.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers2: buffers.size() != sizes.size()" );
  }
    if ( !strides.empty() && buffers.size() != strides.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers2: buffers.size() != strides.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBindVertexBuffers2( m_commandBuffer, firstBinding, buffers.size(), reinterpret_cast<const VkBuffer *>( buffers.data() ), reinterpret_cast<const VkDeviceSize *>( offsets.data() ), reinterpret_cast<const VkDeviceSize *>( sizes.data() ), reinterpret_cast<const VkDeviceSize *>( strides.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthTestEnable( VULKAN_HPP_NAMESPACE::Bool32 depthTestEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthTestEnable( m_commandBuffer, static_cast<VkBool32>( depthTestEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthWriteEnable( VULKAN_HPP_NAMESPACE::Bool32 depthWriteEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthWriteEnable( m_commandBuffer, static_cast<VkBool32>( depthWriteEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthCompareOp( VULKAN_HPP_NAMESPACE::CompareOp depthCompareOp, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthCompareOp( m_commandBuffer, static_cast<VkCompareOp>( depthCompareOp ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthBoundsTestEnable( VULKAN_HPP_NAMESPACE::Bool32 depthBoundsTestEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthBoundsTestEnable( m_commandBuffer, static_cast<VkBool32>( depthBoundsTestEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilTestEnable( VULKAN_HPP_NAMESPACE::Bool32 stencilTestEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilTestEnable( m_commandBuffer, static_cast<VkBool32>( stencilTestEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilOp( VULKAN_HPP_NAMESPACE::StencilFaceFlags faceMask, VULKAN_HPP_NAMESPACE::StencilOp failOp, VULKAN_HPP_NAMESPACE::StencilOp passOp, VULKAN_HPP_NAMESPACE::StencilOp depthFailOp, VULKAN_HPP_NAMESPACE::CompareOp compareOp, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilOp( m_commandBuffer, static_cast<VkStencilFaceFlags>( faceMask ), static_cast<VkStencilOp>( failOp ), static_cast<VkStencilOp>( passOp ), static_cast<VkStencilOp>( depthFailOp ), static_cast<VkCompareOp>( compareOp ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setRasterizerDiscardEnable( VULKAN_HPP_NAMESPACE::Bool32 rasterizerDiscardEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetRasterizerDiscardEnable( m_commandBuffer, static_cast<VkBool32>( rasterizerDiscardEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthBiasEnable( VULKAN_HPP_NAMESPACE::Bool32 depthBiasEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthBiasEnable( m_commandBuffer, static_cast<VkBool32>( depthBiasEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setPrimitiveRestartEnable( VULKAN_HPP_NAMESPACE::Bool32 primitiveRestartEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetPrimitiveRestartEnable( m_commandBuffer, static_cast<VkBool32>( primitiveRestartEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getBufferMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceBufferMemoryRequirements * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceBufferMemoryRequirements( m_device, reinterpret_cast<const VkDeviceBufferMemoryRequirements *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getBufferMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceBufferMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetDeviceBufferMemoryRequirements( m_device, reinterpret_cast<const VkDeviceBufferMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getBufferMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceBufferMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetDeviceBufferMemoryRequirements( m_device, reinterpret_cast<const VkDeviceBufferMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceImageMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getImageMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetDeviceImageMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getImageMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetDeviceImageMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageSparseMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements * pInfo, uint32_t * pSparseMemoryRequirementCount, VULKAN_HPP_NAMESPACE::SparseImageMemoryRequirements2 * pSparseMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceImageSparseMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( pInfo ), pSparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( pSparseMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements;
    uint32_t sparseMemoryRequirementCount;
    d.vkGetDeviceImageSparseMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetDeviceImageSparseMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }

  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageMemoryRequirements2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirements( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, SparseImageMemoryRequirements2Allocator & sparseImageMemoryRequirements2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements( sparseImageMemoryRequirements2Allocator );
    uint32_t sparseMemoryRequirementCount;
    d.vkGetDeviceImageSparseMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetDeviceImageSparseMemoryRequirements( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_surface ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroySurfaceKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySurfaceKHR( m_instance, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroySurfaceKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySurfaceKHR( m_instance, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySurfaceKHR( m_instance, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySurfaceKHR( m_instance, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfaceSupportKHR( uint32_t queueFamilyIndex, VULKAN_HPP_NAMESPACE::SurfaceKHR surface, VULKAN_HPP_NAMESPACE::Bool32 * pSupported, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfaceSupportKHR( m_physicalDevice, queueFamilyIndex, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkBool32 *>( pSupported ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Bool32 >::type PhysicalDevice::getSurfaceSupportKHR( uint32_t queueFamilyIndex, VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Bool32  supported;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceSupportKHR( m_physicalDevice, queueFamilyIndex, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkBool32 *>( &supported ) ) );
    return createResultValue( result, supported, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getSurfaceSupportKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfaceCapabilitiesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, VULKAN_HPP_NAMESPACE::SurfaceCapabilitiesKHR * pSurfaceCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilitiesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkSurfaceCapabilitiesKHR *>( pSurfaceCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceCapabilitiesKHR >::type PhysicalDevice::getSurfaceCapabilitiesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceCapabilitiesKHR  surfaceCapabilities;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilitiesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkSurfaceCapabilitiesKHR *>( &surfaceCapabilities ) ) );
    return createResultValue( result, surfaceCapabilities, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getSurfaceCapabilitiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfaceFormatsKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, uint32_t * pSurfaceFormatCount, VULKAN_HPP_NAMESPACE::SurfaceFormatKHR * pSurfaceFormats, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormatsKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), pSurfaceFormatCount, reinterpret_cast<VkSurfaceFormatKHR *>( pSurfaceFormats ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SurfaceFormatKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<SurfaceFormatKHR, SurfaceFormatKHRAllocator>>::type PhysicalDevice::getSurfaceFormatsKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SurfaceFormatKHR, SurfaceFormatKHRAllocator> surfaceFormats;
    uint32_t surfaceFormatCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormatsKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &surfaceFormatCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && surfaceFormatCount )
      {
        surfaceFormats.resize( surfaceFormatCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormatsKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &surfaceFormatCount, reinterpret_cast<VkSurfaceFormatKHR *>( surfaceFormats.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( surfaceFormatCount <= surfaceFormats.size() );
      if ( surfaceFormatCount < surfaceFormats.size() )
      {
        surfaceFormats.resize( surfaceFormatCount );
      }
    }
    return createResultValue( result, surfaceFormats, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfaceFormatsKHR" );
  }

  template <typename SurfaceFormatKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SurfaceFormatKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<SurfaceFormatKHR, SurfaceFormatKHRAllocator>>::type PhysicalDevice::getSurfaceFormatsKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, SurfaceFormatKHRAllocator & surfaceFormatKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SurfaceFormatKHR, SurfaceFormatKHRAllocator> surfaceFormats( surfaceFormatKHRAllocator );
    uint32_t surfaceFormatCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormatsKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &surfaceFormatCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && surfaceFormatCount )
      {
        surfaceFormats.resize( surfaceFormatCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormatsKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &surfaceFormatCount, reinterpret_cast<VkSurfaceFormatKHR *>( surfaceFormats.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( surfaceFormatCount <= surfaceFormats.size() );
      if ( surfaceFormatCount < surfaceFormats.size() )
      {
        surfaceFormats.resize( surfaceFormatCount );
      }
    }
    return createResultValue( result, surfaceFormats, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfaceFormatsKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfacePresentModesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, uint32_t * pPresentModeCount, VULKAN_HPP_NAMESPACE::PresentModeKHR * pPresentModes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), pPresentModeCount, reinterpret_cast<VkPresentModeKHR *>( pPresentModes ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PresentModeKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PresentModeKHR, PresentModeKHRAllocator>>::type PhysicalDevice::getSurfacePresentModesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PresentModeKHR, PresentModeKHRAllocator> presentModes;
    uint32_t presentModeCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &presentModeCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && presentModeCount )
      {
        presentModes.resize( presentModeCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &presentModeCount, reinterpret_cast<VkPresentModeKHR *>( presentModes.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( presentModeCount <= presentModes.size() );
      if ( presentModeCount < presentModes.size() )
      {
        presentModes.resize( presentModeCount );
      }
    }
    return createResultValue( result, presentModes, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfacePresentModesKHR" );
  }

  template <typename PresentModeKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PresentModeKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PresentModeKHR, PresentModeKHRAllocator>>::type PhysicalDevice::getSurfacePresentModesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, PresentModeKHRAllocator & presentModeKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PresentModeKHR, PresentModeKHRAllocator> presentModes( presentModeKHRAllocator );
    uint32_t presentModeCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &presentModeCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && presentModeCount )
      {
        presentModes.resize( presentModeCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &presentModeCount, reinterpret_cast<VkPresentModeKHR *>( presentModes.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( presentModeCount <= presentModes.size() );
      if ( presentModeCount < presentModes.size() )
      {
        presentModes.resize( presentModeCount );
      }
    }
    return createResultValue( result, presentModes, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfacePresentModesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_swapchain ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createSwapchainKHR( const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SwapchainKHR * pSwapchain, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateSwapchainKHR( m_device, reinterpret_cast<const VkSwapchainCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSwapchainKHR *>( pSwapchain ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SwapchainKHR >::type Device::createSwapchainKHR( const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SwapchainKHR  swapchain;
    Result result = static_cast<Result>( d.vkCreateSwapchainKHR( m_device, reinterpret_cast<const VkSwapchainCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( &swapchain ) ) );
    return createResultValue( result, swapchain, VULKAN_HPP_NAMESPACE_STRING "::Device::createSwapchainKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SwapchainKHR, Dispatch>>::type Device::createSwapchainKHRUnique( const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain;
    Result result = static_cast<Result>( d.vkCreateSwapchainKHR( m_device, reinterpret_cast<const VkSwapchainCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( &swapchain ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SwapchainKHR, Dispatch>( result, swapchain, VULKAN_HPP_NAMESPACE_STRING "::Device::createSwapchainKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySwapchainKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySwapchainKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySwapchainKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySwapchainKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySwapchainKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySwapchainKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSwapchainImagesKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, uint32_t * pSwapchainImageCount, VULKAN_HPP_NAMESPACE::Image * pSwapchainImages, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSwapchainImagesKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), pSwapchainImageCount, reinterpret_cast<VkImage *>( pSwapchainImages ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename ImageAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<Image, ImageAllocator>>::type Device::getSwapchainImagesKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<Image, ImageAllocator> swapchainImages;
    uint32_t swapchainImageCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetSwapchainImagesKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), &swapchainImageCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && swapchainImageCount )
      {
        swapchainImages.resize( swapchainImageCount );
        result = static_cast<Result>( d.vkGetSwapchainImagesKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), &swapchainImageCount, reinterpret_cast<VkImage *>( swapchainImages.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( swapchainImageCount <= swapchainImages.size() );
      if ( swapchainImageCount < swapchainImages.size() )
      {
        swapchainImages.resize( swapchainImageCount );
      }
    }
    return createResultValue( result, swapchainImages, VULKAN_HPP_NAMESPACE_STRING"::Device::getSwapchainImagesKHR" );
  }

  template <typename ImageAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, Image>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<Image, ImageAllocator>>::type Device::getSwapchainImagesKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, ImageAllocator & imageAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<Image, ImageAllocator> swapchainImages( imageAllocator );
    uint32_t swapchainImageCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetSwapchainImagesKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), &swapchainImageCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && swapchainImageCount )
      {
        swapchainImages.resize( swapchainImageCount );
        result = static_cast<Result>( d.vkGetSwapchainImagesKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), &swapchainImageCount, reinterpret_cast<VkImage *>( swapchainImages.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( swapchainImageCount <= swapchainImages.size() );
      if ( swapchainImageCount < swapchainImages.size() )
      {
        swapchainImages.resize( swapchainImageCount );
      }
    }
    return createResultValue( result, swapchainImages, VULKAN_HPP_NAMESPACE_STRING"::Device::getSwapchainImagesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::acquireNextImageKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, uint64_t timeout, VULKAN_HPP_NAMESPACE::Semaphore semaphore, VULKAN_HPP_NAMESPACE::Fence fence, uint32_t * pImageIndex, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireNextImageKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), timeout, static_cast<VkSemaphore>( semaphore ), static_cast<VkFence>( fence ), pImageIndex ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<uint32_t > Device::acquireNextImageKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, uint64_t timeout, VULKAN_HPP_NAMESPACE::Semaphore semaphore, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint32_t  imageIndex;
    Result result = static_cast<Result>( d.vkAcquireNextImageKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), timeout, static_cast<VkSemaphore>( semaphore ), static_cast<VkFence>( fence ), &imageIndex ) );
    return createResultValue( result, imageIndex, VULKAN_HPP_NAMESPACE_STRING "::Device::acquireNextImageKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eTimeout, VULKAN_HPP_NAMESPACE::Result::eNotReady, VULKAN_HPP_NAMESPACE::Result::eSuboptimalKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::presentKHR( const VULKAN_HPP_NAMESPACE::PresentInfoKHR * pPresentInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueuePresentKHR( m_queue, reinterpret_cast<const VkPresentInfoKHR *>( pPresentInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::presentKHR( const VULKAN_HPP_NAMESPACE::PresentInfoKHR & presentInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueuePresentKHR( m_queue, reinterpret_cast<const VkPresentInfoKHR *>( &presentInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::presentKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eSuboptimalKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getGroupPresentCapabilitiesKHR( VULKAN_HPP_NAMESPACE::DeviceGroupPresentCapabilitiesKHR * pDeviceGroupPresentCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDeviceGroupPresentCapabilitiesKHR( m_device, reinterpret_cast<VkDeviceGroupPresentCapabilitiesKHR *>( pDeviceGroupPresentCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DeviceGroupPresentCapabilitiesKHR >::type Device::getGroupPresentCapabilitiesKHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DeviceGroupPresentCapabilitiesKHR  deviceGroupPresentCapabilities;
    Result result = static_cast<Result>( d.vkGetDeviceGroupPresentCapabilitiesKHR( m_device, reinterpret_cast<VkDeviceGroupPresentCapabilitiesKHR *>( &deviceGroupPresentCapabilities ) ) );
    return createResultValue( result, deviceGroupPresentCapabilities, VULKAN_HPP_NAMESPACE_STRING "::Device::getGroupPresentCapabilitiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getGroupSurfacePresentModesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, VULKAN_HPP_NAMESPACE::DeviceGroupPresentModeFlagsKHR * pModes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDeviceGroupSurfacePresentModesKHR( m_device, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR *>( pModes ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DeviceGroupPresentModeFlagsKHR >::type Device::getGroupSurfacePresentModesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DeviceGroupPresentModeFlagsKHR  modes;
    Result result = static_cast<Result>( d.vkGetDeviceGroupSurfacePresentModesKHR( m_device, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR *>( &modes ) ) );
    return createResultValue( result, modes, VULKAN_HPP_NAMESPACE_STRING "::Device::getGroupSurfacePresentModesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getPresentRectanglesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, uint32_t * pRectCount, VULKAN_HPP_NAMESPACE::Rect2D * pRects, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDevicePresentRectanglesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), pRectCount, reinterpret_cast<VkRect2D *>( pRects ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Rect2DAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<Rect2D, Rect2DAllocator>>::type PhysicalDevice::getPresentRectanglesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<Rect2D, Rect2DAllocator> rects;
    uint32_t rectCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDevicePresentRectanglesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &rectCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && rectCount )
      {
        rects.resize( rectCount );
        result = static_cast<Result>( d.vkGetPhysicalDevicePresentRectanglesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &rectCount, reinterpret_cast<VkRect2D *>( rects.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( rectCount <= rects.size() );
      if ( rectCount < rects.size() )
      {
        rects.resize( rectCount );
      }
    }
    return createResultValue( result, rects, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getPresentRectanglesKHR" );
  }

  template <typename Rect2DAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, Rect2D>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<Rect2D, Rect2DAllocator>>::type PhysicalDevice::getPresentRectanglesKHR( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Rect2DAllocator & rect2DAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<Rect2D, Rect2DAllocator> rects( rect2DAllocator );
    uint32_t rectCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDevicePresentRectanglesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &rectCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && rectCount )
      {
        rects.resize( rectCount );
        result = static_cast<Result>( d.vkGetPhysicalDevicePresentRectanglesKHR( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), &rectCount, reinterpret_cast<VkRect2D *>( rects.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( rectCount <= rects.size() );
      if ( rectCount < rects.size() )
      {
        rects.resize( rectCount );
      }
    }
    return createResultValue( result, rects, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getPresentRectanglesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::acquireNextImage2KHR( const VULKAN_HPP_NAMESPACE::AcquireNextImageInfoKHR * pAcquireInfo, uint32_t * pImageIndex, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireNextImage2KHR( m_device, reinterpret_cast<const VkAcquireNextImageInfoKHR *>( pAcquireInfo ), pImageIndex ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<uint32_t > Device::acquireNextImage2KHR( const VULKAN_HPP_NAMESPACE::AcquireNextImageInfoKHR & acquireInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint32_t  imageIndex;
    Result result = static_cast<Result>( d.vkAcquireNextImage2KHR( m_device, reinterpret_cast<const VkAcquireNextImageInfoKHR *>( &acquireInfo ), &imageIndex ) );
    return createResultValue( result, imageIndex, VULKAN_HPP_NAMESPACE_STRING "::Device::acquireNextImage2KHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eTimeout, VULKAN_HPP_NAMESPACE::Result::eNotReady, VULKAN_HPP_NAMESPACE::Result::eSuboptimalKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_display ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayPropertiesKHR( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::DisplayPropertiesKHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceDisplayPropertiesKHR( m_physicalDevice, pPropertyCount, reinterpret_cast<VkDisplayPropertiesKHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayPropertiesKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayPropertiesKHR, DisplayPropertiesKHRAllocator>>::type PhysicalDevice::getDisplayPropertiesKHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayPropertiesKHR, DisplayPropertiesKHRAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPropertiesKHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPropertiesKHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayPropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPropertiesKHR" );
  }

  template <typename DisplayPropertiesKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayPropertiesKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayPropertiesKHR, DisplayPropertiesKHRAllocator>>::type PhysicalDevice::getDisplayPropertiesKHR( DisplayPropertiesKHRAllocator & displayPropertiesKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayPropertiesKHR, DisplayPropertiesKHRAllocator> properties( displayPropertiesKHRAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPropertiesKHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPropertiesKHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayPropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayPlanePropertiesKHR( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::DisplayPlanePropertiesKHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlanePropertiesKHR( m_physicalDevice, pPropertyCount, reinterpret_cast<VkDisplayPlanePropertiesKHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayPlanePropertiesKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayPlanePropertiesKHR, DisplayPlanePropertiesKHRAllocator>>::type PhysicalDevice::getDisplayPlanePropertiesKHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayPlanePropertiesKHR, DisplayPlanePropertiesKHRAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlanePropertiesKHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlanePropertiesKHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayPlanePropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPlanePropertiesKHR" );
  }

  template <typename DisplayPlanePropertiesKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayPlanePropertiesKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayPlanePropertiesKHR, DisplayPlanePropertiesKHRAllocator>>::type PhysicalDevice::getDisplayPlanePropertiesKHR( DisplayPlanePropertiesKHRAllocator & displayPlanePropertiesKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayPlanePropertiesKHR, DisplayPlanePropertiesKHRAllocator> properties( displayPlanePropertiesKHRAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlanePropertiesKHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlanePropertiesKHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayPlanePropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPlanePropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayPlaneSupportedDisplaysKHR( uint32_t planeIndex, uint32_t * pDisplayCount, VULKAN_HPP_NAMESPACE::DisplayKHR * pDisplays, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDisplayPlaneSupportedDisplaysKHR( m_physicalDevice, planeIndex, pDisplayCount, reinterpret_cast<VkDisplayKHR *>( pDisplays ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayKHR, DisplayKHRAllocator>>::type PhysicalDevice::getDisplayPlaneSupportedDisplaysKHR( uint32_t planeIndex, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayKHR, DisplayKHRAllocator> displays;
    uint32_t displayCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetDisplayPlaneSupportedDisplaysKHR( m_physicalDevice, planeIndex, &displayCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && displayCount )
      {
        displays.resize( displayCount );
        result = static_cast<Result>( d.vkGetDisplayPlaneSupportedDisplaysKHR( m_physicalDevice, planeIndex, &displayCount, reinterpret_cast<VkDisplayKHR *>( displays.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( displayCount <= displays.size() );
      if ( displayCount < displays.size() )
      {
        displays.resize( displayCount );
      }
    }
    return createResultValue( result, displays, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPlaneSupportedDisplaysKHR" );
  }

  template <typename DisplayKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayKHR, DisplayKHRAllocator>>::type PhysicalDevice::getDisplayPlaneSupportedDisplaysKHR( uint32_t planeIndex, DisplayKHRAllocator & displayKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayKHR, DisplayKHRAllocator> displays( displayKHRAllocator );
    uint32_t displayCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetDisplayPlaneSupportedDisplaysKHR( m_physicalDevice, planeIndex, &displayCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && displayCount )
      {
        displays.resize( displayCount );
        result = static_cast<Result>( d.vkGetDisplayPlaneSupportedDisplaysKHR( m_physicalDevice, planeIndex, &displayCount, reinterpret_cast<VkDisplayKHR *>( displays.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( displayCount <= displays.size() );
      if ( displayCount < displays.size() )
      {
        displays.resize( displayCount );
      }
    }
    return createResultValue( result, displays, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPlaneSupportedDisplaysKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayModePropertiesKHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::DisplayModePropertiesKHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDisplayModePropertiesKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), pPropertyCount, reinterpret_cast<VkDisplayModePropertiesKHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayModePropertiesKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayModePropertiesKHR, DisplayModePropertiesKHRAllocator>>::type PhysicalDevice::getDisplayModePropertiesKHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayModePropertiesKHR, DisplayModePropertiesKHRAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetDisplayModePropertiesKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetDisplayModePropertiesKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, reinterpret_cast<VkDisplayModePropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayModePropertiesKHR" );
  }

  template <typename DisplayModePropertiesKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayModePropertiesKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayModePropertiesKHR, DisplayModePropertiesKHRAllocator>>::type PhysicalDevice::getDisplayModePropertiesKHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, DisplayModePropertiesKHRAllocator & displayModePropertiesKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayModePropertiesKHR, DisplayModePropertiesKHRAllocator> properties( displayModePropertiesKHRAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetDisplayModePropertiesKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetDisplayModePropertiesKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, reinterpret_cast<VkDisplayModePropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayModePropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::createDisplayModeKHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayModeCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DisplayModeKHR * pMode, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDisplayModeKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayModeCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDisplayModeKHR *>( pMode ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DisplayModeKHR >::type PhysicalDevice::createDisplayModeKHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayModeCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DisplayModeKHR  mode;
    Result result = static_cast<Result>( d.vkCreateDisplayModeKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayModeCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDisplayModeKHR *>( &mode ) ) );
    return createResultValue( result, mode, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::createDisplayModeKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DisplayModeKHR, Dispatch>>::type PhysicalDevice::createDisplayModeKHRUnique( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayModeCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DisplayModeKHR mode;
    Result result = static_cast<Result>( d.vkCreateDisplayModeKHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayModeCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDisplayModeKHR *>( &mode ) ) );
    ObjectDestroy<PhysicalDevice, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DisplayModeKHR, Dispatch>( result, mode, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::createDisplayModeKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayPlaneCapabilitiesKHR( VULKAN_HPP_NAMESPACE::DisplayModeKHR mode, uint32_t planeIndex, VULKAN_HPP_NAMESPACE::DisplayPlaneCapabilitiesKHR * pCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDisplayPlaneCapabilitiesKHR( m_physicalDevice, static_cast<VkDisplayModeKHR>( mode ), planeIndex, reinterpret_cast<VkDisplayPlaneCapabilitiesKHR *>( pCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DisplayPlaneCapabilitiesKHR >::type PhysicalDevice::getDisplayPlaneCapabilitiesKHR( VULKAN_HPP_NAMESPACE::DisplayModeKHR mode, uint32_t planeIndex, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DisplayPlaneCapabilitiesKHR  capabilities;
    Result result = static_cast<Result>( d.vkGetDisplayPlaneCapabilitiesKHR( m_physicalDevice, static_cast<VkDisplayModeKHR>( mode ), planeIndex, reinterpret_cast<VkDisplayPlaneCapabilitiesKHR *>( &capabilities ) ) );
    return createResultValue( result, capabilities, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getDisplayPlaneCapabilitiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createDisplayPlaneSurfaceKHR( const VULKAN_HPP_NAMESPACE::DisplaySurfaceCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDisplayPlaneSurfaceKHR( m_instance, reinterpret_cast<const VkDisplaySurfaceCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createDisplayPlaneSurfaceKHR( const VULKAN_HPP_NAMESPACE::DisplaySurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateDisplayPlaneSurfaceKHR( m_instance, reinterpret_cast<const VkDisplaySurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDisplayPlaneSurfaceKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createDisplayPlaneSurfaceKHRUnique( const VULKAN_HPP_NAMESPACE::DisplaySurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateDisplayPlaneSurfaceKHR( m_instance, reinterpret_cast<const VkDisplaySurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDisplayPlaneSurfaceKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_display_swapchain ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createSharedSwapchainsKHR( uint32_t swapchainCount, const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR * pCreateInfos, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SwapchainKHR * pSwapchains, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, swapchainCount, reinterpret_cast<const VkSwapchainCreateInfoKHR *>( pCreateInfos ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSwapchainKHR *>( pSwapchains ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SwapchainKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<VULKAN_HPP_NAMESPACE::SwapchainKHR, SwapchainKHRAllocator>>::type Device::createSharedSwapchainsKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::SwapchainKHR, SwapchainKHRAllocator> swapchains( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, createInfos.size(), reinterpret_cast<const VkSwapchainCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( swapchains.data() ) ) );
    return createResultValue( result, swapchains, VULKAN_HPP_NAMESPACE_STRING "::Device::createSharedSwapchainsKHR" );
  }

  template <typename SwapchainKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SwapchainKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<VULKAN_HPP_NAMESPACE::SwapchainKHR, SwapchainKHRAllocator>>::type Device::createSharedSwapchainsKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, SwapchainKHRAllocator & swapchainKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::SwapchainKHR, SwapchainKHRAllocator> swapchains( createInfos.size(), swapchainKHRAllocator );
    Result result = static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, createInfos.size(), reinterpret_cast<const VkSwapchainCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( swapchains.data() ) ) );
    return createResultValue( result, swapchains, VULKAN_HPP_NAMESPACE_STRING "::Device::createSharedSwapchainsKHR" );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SwapchainKHR >::type Device::createSharedSwapchainKHR( const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SwapchainKHR  swapchain;
    Result result = static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, 1, reinterpret_cast<const VkSwapchainCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( &swapchain ) ) );
    return createResultValue( result, swapchain, VULKAN_HPP_NAMESPACE_STRING "::Device::createSharedSwapchainKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename SwapchainKHRAllocator>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<UniqueHandle<SwapchainKHR, Dispatch>, SwapchainKHRAllocator>>::type Device::createSharedSwapchainsKHRUnique( ArrayProxy<const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<SwapchainKHR, Dispatch>, SwapchainKHRAllocator> uniqueSwapchains;
    std::vector<SwapchainKHR> swapchains( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, createInfos.size(), reinterpret_cast<const VkSwapchainCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( swapchains.data() ) ) );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      uniqueSwapchains.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniqueSwapchains.push_back( UniqueHandle<SwapchainKHR, Dispatch>( swapchains[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniqueSwapchains ), VULKAN_HPP_NAMESPACE_STRING "::Device::createSharedSwapchainsKHRUnique" );
  }

  template <typename Dispatch, typename SwapchainKHRAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<SwapchainKHR, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<UniqueHandle<SwapchainKHR, Dispatch>, SwapchainKHRAllocator>>::type Device::createSharedSwapchainsKHRUnique( ArrayProxy<const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, SwapchainKHRAllocator & swapchainKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<SwapchainKHR, Dispatch>, SwapchainKHRAllocator> uniqueSwapchains( swapchainKHRAllocator );
    std::vector<SwapchainKHR> swapchains( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, createInfos.size(), reinterpret_cast<const VkSwapchainCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( swapchains.data() ) ) );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      uniqueSwapchains.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniqueSwapchains.push_back( UniqueHandle<SwapchainKHR, Dispatch>( swapchains[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniqueSwapchains ), VULKAN_HPP_NAMESPACE_STRING "::Device::createSharedSwapchainsKHRUnique" );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<SwapchainKHR, Dispatch>>::type Device::createSharedSwapchainKHRUnique( const VULKAN_HPP_NAMESPACE::SwapchainCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    SwapchainKHR swapchain;
    Result result = static_cast<Result>( d.vkCreateSharedSwapchainsKHR( m_device, 1, reinterpret_cast<const VkSwapchainCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSwapchainKHR *>( &swapchain ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<SwapchainKHR, Dispatch>( result, swapchain, VULKAN_HPP_NAMESPACE_STRING "::Device::createSharedSwapchainKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_XLIB_KHR )
  //=== VK_KHR_xlib_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createXlibSurfaceKHR( const VULKAN_HPP_NAMESPACE::XlibSurfaceCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateXlibSurfaceKHR( m_instance, reinterpret_cast<const VkXlibSurfaceCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createXlibSurfaceKHR( const VULKAN_HPP_NAMESPACE::XlibSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateXlibSurfaceKHR( m_instance, reinterpret_cast<const VkXlibSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createXlibSurfaceKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createXlibSurfaceKHRUnique( const VULKAN_HPP_NAMESPACE::XlibSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateXlibSurfaceKHR( m_instance, reinterpret_cast<const VkXlibSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createXlibSurfaceKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getXlibPresentationSupportKHR( uint32_t queueFamilyIndex, Display * dpy, VisualID visualID, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Bool32>( d.vkGetPhysicalDeviceXlibPresentationSupportKHR( m_physicalDevice, queueFamilyIndex, dpy, visualID ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getXlibPresentationSupportKHR( uint32_t queueFamilyIndex, Display & dpy, VisualID visualID, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetPhysicalDeviceXlibPresentationSupportKHR( m_physicalDevice, queueFamilyIndex, &dpy, visualID );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_XLIB_KHR*/

#if defined( VK_USE_PLATFORM_XCB_KHR )
  //=== VK_KHR_xcb_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createXcbSurfaceKHR( const VULKAN_HPP_NAMESPACE::XcbSurfaceCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateXcbSurfaceKHR( m_instance, reinterpret_cast<const VkXcbSurfaceCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createXcbSurfaceKHR( const VULKAN_HPP_NAMESPACE::XcbSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateXcbSurfaceKHR( m_instance, reinterpret_cast<const VkXcbSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createXcbSurfaceKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createXcbSurfaceKHRUnique( const VULKAN_HPP_NAMESPACE::XcbSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateXcbSurfaceKHR( m_instance, reinterpret_cast<const VkXcbSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createXcbSurfaceKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getXcbPresentationSupportKHR( uint32_t queueFamilyIndex, xcb_connection_t * connection, xcb_visualid_t visual_id, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Bool32>( d.vkGetPhysicalDeviceXcbPresentationSupportKHR( m_physicalDevice, queueFamilyIndex, connection, visual_id ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getXcbPresentationSupportKHR( uint32_t queueFamilyIndex, xcb_connection_t & connection, xcb_visualid_t visual_id, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetPhysicalDeviceXcbPresentationSupportKHR( m_physicalDevice, queueFamilyIndex, &connection, visual_id );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_XCB_KHR*/

#if defined( VK_USE_PLATFORM_WAYLAND_KHR )
  //=== VK_KHR_wayland_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createWaylandSurfaceKHR( const VULKAN_HPP_NAMESPACE::WaylandSurfaceCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateWaylandSurfaceKHR( m_instance, reinterpret_cast<const VkWaylandSurfaceCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createWaylandSurfaceKHR( const VULKAN_HPP_NAMESPACE::WaylandSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateWaylandSurfaceKHR( m_instance, reinterpret_cast<const VkWaylandSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createWaylandSurfaceKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createWaylandSurfaceKHRUnique( const VULKAN_HPP_NAMESPACE::WaylandSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateWaylandSurfaceKHR( m_instance, reinterpret_cast<const VkWaylandSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createWaylandSurfaceKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getWaylandPresentationSupportKHR( uint32_t queueFamilyIndex, struct wl_display * display, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Bool32>( d.vkGetPhysicalDeviceWaylandPresentationSupportKHR( m_physicalDevice, queueFamilyIndex, display ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getWaylandPresentationSupportKHR( uint32_t queueFamilyIndex, struct wl_display & display, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetPhysicalDeviceWaylandPresentationSupportKHR( m_physicalDevice, queueFamilyIndex, &display );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WAYLAND_KHR*/

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_KHR_android_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createAndroidSurfaceKHR( const VULKAN_HPP_NAMESPACE::AndroidSurfaceCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateAndroidSurfaceKHR( m_instance, reinterpret_cast<const VkAndroidSurfaceCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createAndroidSurfaceKHR( const VULKAN_HPP_NAMESPACE::AndroidSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateAndroidSurfaceKHR( m_instance, reinterpret_cast<const VkAndroidSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createAndroidSurfaceKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createAndroidSurfaceKHRUnique( const VULKAN_HPP_NAMESPACE::AndroidSurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateAndroidSurfaceKHR( m_instance, reinterpret_cast<const VkAndroidSurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createAndroidSurfaceKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_win32_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createWin32SurfaceKHR( const VULKAN_HPP_NAMESPACE::Win32SurfaceCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateWin32SurfaceKHR( m_instance, reinterpret_cast<const VkWin32SurfaceCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createWin32SurfaceKHR( const VULKAN_HPP_NAMESPACE::Win32SurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateWin32SurfaceKHR( m_instance, reinterpret_cast<const VkWin32SurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createWin32SurfaceKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createWin32SurfaceKHRUnique( const VULKAN_HPP_NAMESPACE::Win32SurfaceCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateWin32SurfaceKHR( m_instance, reinterpret_cast<const VkWin32SurfaceCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createWin32SurfaceKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getWin32PresentationSupportKHR( uint32_t queueFamilyIndex, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Bool32>( d.vkGetPhysicalDeviceWin32PresentationSupportKHR( m_physicalDevice, queueFamilyIndex ) );
  }
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_debug_report ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createDebugReportCallbackEXT( const VULKAN_HPP_NAMESPACE::DebugReportCallbackCreateInfoEXT * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT * pCallback, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDebugReportCallbackEXT( m_instance, reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDebugReportCallbackEXT *>( pCallback ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT >::type Instance::createDebugReportCallbackEXT( const VULKAN_HPP_NAMESPACE::DebugReportCallbackCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT  callback;
    Result result = static_cast<Result>( d.vkCreateDebugReportCallbackEXT( m_instance, reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDebugReportCallbackEXT *>( &callback ) ) );
    return createResultValue( result, callback, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDebugReportCallbackEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT, Dispatch>>::type Instance::createDebugReportCallbackEXTUnique( const VULKAN_HPP_NAMESPACE::DebugReportCallbackCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT callback;
    Result result = static_cast<Result>( d.vkCreateDebugReportCallbackEXT( m_instance, reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDebugReportCallbackEXT *>( &callback ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT, Dispatch>( result, callback, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDebugReportCallbackEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroyDebugReportCallbackEXT( VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT callback, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDebugReportCallbackEXT( m_instance, static_cast<VkDebugReportCallbackEXT>( callback ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroyDebugReportCallbackEXT( VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT callback, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDebugReportCallbackEXT( m_instance, static_cast<VkDebugReportCallbackEXT>( callback ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT callback, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDebugReportCallbackEXT( m_instance, static_cast<VkDebugReportCallbackEXT>( callback ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( VULKAN_HPP_NAMESPACE::DebugReportCallbackEXT callback, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDebugReportCallbackEXT( m_instance, static_cast<VkDebugReportCallbackEXT>( callback ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::debugReportMessageEXT( VULKAN_HPP_NAMESPACE::DebugReportFlagsEXT flags, VULKAN_HPP_NAMESPACE::DebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char * pLayerPrefix, const char * pMessage, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDebugReportMessageEXT( m_instance, static_cast<VkDebugReportFlagsEXT>( flags ), static_cast<VkDebugReportObjectTypeEXT>( objectType ), object, location, messageCode, pLayerPrefix, pMessage );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::debugReportMessageEXT( VULKAN_HPP_NAMESPACE::DebugReportFlagsEXT flags, VULKAN_HPP_NAMESPACE::DebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const std::string & layerPrefix, const std::string & message, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDebugReportMessageEXT( m_instance, static_cast<VkDebugReportFlagsEXT>( flags ), static_cast<VkDebugReportObjectTypeEXT>( objectType ), object, location, messageCode, layerPrefix.c_str(), message.c_str() );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_debug_marker ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::debugMarkerSetObjectTagEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerObjectTagInfoEXT * pTagInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkDebugMarkerSetObjectTagEXT( m_device, reinterpret_cast<const VkDebugMarkerObjectTagInfoEXT *>( pTagInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::debugMarkerSetObjectTagEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerObjectTagInfoEXT & tagInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkDebugMarkerSetObjectTagEXT( m_device, reinterpret_cast<const VkDebugMarkerObjectTagInfoEXT *>( &tagInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::debugMarkerSetObjectTagEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::debugMarkerSetObjectNameEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerObjectNameInfoEXT * pNameInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkDebugMarkerSetObjectNameEXT( m_device, reinterpret_cast<const VkDebugMarkerObjectNameInfoEXT *>( pNameInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::debugMarkerSetObjectNameEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerObjectNameInfoEXT & nameInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkDebugMarkerSetObjectNameEXT( m_device, reinterpret_cast<const VkDebugMarkerObjectNameInfoEXT *>( &nameInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::debugMarkerSetObjectNameEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::debugMarkerBeginEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerMarkerInfoEXT * pMarkerInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDebugMarkerBeginEXT( m_commandBuffer, reinterpret_cast<const VkDebugMarkerMarkerInfoEXT *>( pMarkerInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::debugMarkerBeginEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerMarkerInfoEXT & markerInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdDebugMarkerBeginEXT( m_commandBuffer, reinterpret_cast<const VkDebugMarkerMarkerInfoEXT *>( &markerInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::debugMarkerEndEXT( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDebugMarkerEndEXT( m_commandBuffer );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::debugMarkerInsertEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerMarkerInfoEXT * pMarkerInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDebugMarkerInsertEXT( m_commandBuffer, reinterpret_cast<const VkDebugMarkerMarkerInfoEXT *>( pMarkerInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::debugMarkerInsertEXT( const VULKAN_HPP_NAMESPACE::DebugMarkerMarkerInfoEXT & markerInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdDebugMarkerInsertEXT( m_commandBuffer, reinterpret_cast<const VkDebugMarkerMarkerInfoEXT *>( &markerInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_KHR_video_queue ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getVideoCapabilitiesKHR( const VULKAN_HPP_NAMESPACE::VideoProfileKHR * pVideoProfile, VULKAN_HPP_NAMESPACE::VideoCapabilitiesKHR * pCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceVideoCapabilitiesKHR( m_physicalDevice, reinterpret_cast<const VkVideoProfileKHR *>( pVideoProfile ), reinterpret_cast<VkVideoCapabilitiesKHR *>( pCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::VideoCapabilitiesKHR >::type PhysicalDevice::getVideoCapabilitiesKHR( const VULKAN_HPP_NAMESPACE::VideoProfileKHR & videoProfile, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::VideoCapabilitiesKHR  capabilities;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceVideoCapabilitiesKHR( m_physicalDevice, reinterpret_cast<const VkVideoProfileKHR *>( &videoProfile ), reinterpret_cast<VkVideoCapabilitiesKHR *>( &capabilities ) ) );
    return createResultValue( result, capabilities, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getVideoCapabilitiesKHR" );
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<StructureChain<X, Y, Z...>>::type PhysicalDevice::getVideoCapabilitiesKHR( const VULKAN_HPP_NAMESPACE::VideoProfileKHR & videoProfile, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::VideoCapabilitiesKHR & capabilities = structureChain.template get<VULKAN_HPP_NAMESPACE::VideoCapabilitiesKHR>();
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceVideoCapabilitiesKHR( m_physicalDevice, reinterpret_cast<const VkVideoProfileKHR *>( &videoProfile ), reinterpret_cast<VkVideoCapabilitiesKHR *>( &capabilities ) ) );
    return createResultValue( result, structureChain, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getVideoCapabilitiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getVideoFormatPropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceVideoFormatInfoKHR * pVideoFormatInfo, uint32_t * pVideoFormatPropertyCount, VULKAN_HPP_NAMESPACE::VideoFormatPropertiesKHR * pVideoFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceVideoFormatPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceVideoFormatInfoKHR *>( pVideoFormatInfo ), pVideoFormatPropertyCount, reinterpret_cast<VkVideoFormatPropertiesKHR *>( pVideoFormatProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename VideoFormatPropertiesKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<VideoFormatPropertiesKHR, VideoFormatPropertiesKHRAllocator>>::type PhysicalDevice::getVideoFormatPropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceVideoFormatInfoKHR & videoFormatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VideoFormatPropertiesKHR, VideoFormatPropertiesKHRAllocator> videoFormatProperties;
    uint32_t videoFormatPropertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceVideoFormatPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceVideoFormatInfoKHR *>( &videoFormatInfo ), &videoFormatPropertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && videoFormatPropertyCount )
      {
        videoFormatProperties.resize( videoFormatPropertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceVideoFormatPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceVideoFormatInfoKHR *>( &videoFormatInfo ), &videoFormatPropertyCount, reinterpret_cast<VkVideoFormatPropertiesKHR *>( videoFormatProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( videoFormatPropertyCount <= videoFormatProperties.size() );
      if ( videoFormatPropertyCount < videoFormatProperties.size() )
      {
        videoFormatProperties.resize( videoFormatPropertyCount );
      }
    }
    return createResultValue( result, videoFormatProperties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getVideoFormatPropertiesKHR" );
  }

  template <typename VideoFormatPropertiesKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, VideoFormatPropertiesKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<VideoFormatPropertiesKHR, VideoFormatPropertiesKHRAllocator>>::type PhysicalDevice::getVideoFormatPropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceVideoFormatInfoKHR & videoFormatInfo, VideoFormatPropertiesKHRAllocator & videoFormatPropertiesKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VideoFormatPropertiesKHR, VideoFormatPropertiesKHRAllocator> videoFormatProperties( videoFormatPropertiesKHRAllocator );
    uint32_t videoFormatPropertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceVideoFormatPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceVideoFormatInfoKHR *>( &videoFormatInfo ), &videoFormatPropertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && videoFormatPropertyCount )
      {
        videoFormatProperties.resize( videoFormatPropertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceVideoFormatPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceVideoFormatInfoKHR *>( &videoFormatInfo ), &videoFormatPropertyCount, reinterpret_cast<VkVideoFormatPropertiesKHR *>( videoFormatProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( videoFormatPropertyCount <= videoFormatProperties.size() );
      if ( videoFormatPropertyCount < videoFormatProperties.size() )
      {
        videoFormatProperties.resize( videoFormatPropertyCount );
      }
    }
    return createResultValue( result, videoFormatProperties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getVideoFormatPropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createVideoSessionKHR( const VULKAN_HPP_NAMESPACE::VideoSessionCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::VideoSessionKHR * pVideoSession, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateVideoSessionKHR( m_device, reinterpret_cast<const VkVideoSessionCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkVideoSessionKHR *>( pVideoSession ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::VideoSessionKHR >::type Device::createVideoSessionKHR( const VULKAN_HPP_NAMESPACE::VideoSessionCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::VideoSessionKHR  videoSession;
    Result result = static_cast<Result>( d.vkCreateVideoSessionKHR( m_device, reinterpret_cast<const VkVideoSessionCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkVideoSessionKHR *>( &videoSession ) ) );
    return createResultValue( result, videoSession, VULKAN_HPP_NAMESPACE_STRING "::Device::createVideoSessionKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::VideoSessionKHR, Dispatch>>::type Device::createVideoSessionKHRUnique( const VULKAN_HPP_NAMESPACE::VideoSessionCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession;
    Result result = static_cast<Result>( d.vkCreateVideoSessionKHR( m_device, reinterpret_cast<const VkVideoSessionCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkVideoSessionKHR *>( &videoSession ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::VideoSessionKHR, Dispatch>( result, videoSession, VULKAN_HPP_NAMESPACE_STRING "::Device::createVideoSessionKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyVideoSessionKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyVideoSessionKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyVideoSessionKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyVideoSessionKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyVideoSessionKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyVideoSessionKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getVideoSessionMemoryRequirementsKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, uint32_t * pVideoSessionMemoryRequirementsCount, VULKAN_HPP_NAMESPACE::VideoGetMemoryPropertiesKHR * pVideoSessionMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetVideoSessionMemoryRequirementsKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), pVideoSessionMemoryRequirementsCount, reinterpret_cast<VkVideoGetMemoryPropertiesKHR *>( pVideoSessionMemoryRequirements ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename VideoGetMemoryPropertiesKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<VideoGetMemoryPropertiesKHR, VideoGetMemoryPropertiesKHRAllocator>>::type Device::getVideoSessionMemoryRequirementsKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VideoGetMemoryPropertiesKHR, VideoGetMemoryPropertiesKHRAllocator> videoSessionMemoryRequirements;
    uint32_t videoSessionMemoryRequirementsCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetVideoSessionMemoryRequirementsKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), &videoSessionMemoryRequirementsCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && videoSessionMemoryRequirementsCount )
      {
        videoSessionMemoryRequirements.resize( videoSessionMemoryRequirementsCount );
        result = static_cast<Result>( d.vkGetVideoSessionMemoryRequirementsKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), &videoSessionMemoryRequirementsCount, reinterpret_cast<VkVideoGetMemoryPropertiesKHR *>( videoSessionMemoryRequirements.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( videoSessionMemoryRequirementsCount <= videoSessionMemoryRequirements.size() );
      if ( videoSessionMemoryRequirementsCount < videoSessionMemoryRequirements.size() )
      {
        videoSessionMemoryRequirements.resize( videoSessionMemoryRequirementsCount );
      }
    }
    return createResultValue( result, videoSessionMemoryRequirements, VULKAN_HPP_NAMESPACE_STRING"::Device::getVideoSessionMemoryRequirementsKHR" );
  }

  template <typename VideoGetMemoryPropertiesKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, VideoGetMemoryPropertiesKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<VideoGetMemoryPropertiesKHR, VideoGetMemoryPropertiesKHRAllocator>>::type Device::getVideoSessionMemoryRequirementsKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, VideoGetMemoryPropertiesKHRAllocator & videoGetMemoryPropertiesKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VideoGetMemoryPropertiesKHR, VideoGetMemoryPropertiesKHRAllocator> videoSessionMemoryRequirements( videoGetMemoryPropertiesKHRAllocator );
    uint32_t videoSessionMemoryRequirementsCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetVideoSessionMemoryRequirementsKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), &videoSessionMemoryRequirementsCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && videoSessionMemoryRequirementsCount )
      {
        videoSessionMemoryRequirements.resize( videoSessionMemoryRequirementsCount );
        result = static_cast<Result>( d.vkGetVideoSessionMemoryRequirementsKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), &videoSessionMemoryRequirementsCount, reinterpret_cast<VkVideoGetMemoryPropertiesKHR *>( videoSessionMemoryRequirements.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( videoSessionMemoryRequirementsCount <= videoSessionMemoryRequirements.size() );
      if ( videoSessionMemoryRequirementsCount < videoSessionMemoryRequirements.size() )
      {
        videoSessionMemoryRequirements.resize( videoSessionMemoryRequirementsCount );
      }
    }
    return createResultValue( result, videoSessionMemoryRequirements, VULKAN_HPP_NAMESPACE_STRING"::Device::getVideoSessionMemoryRequirementsKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindVideoSessionMemoryKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, uint32_t videoSessionBindMemoryCount, const VULKAN_HPP_NAMESPACE::VideoBindMemoryKHR * pVideoSessionBindMemories, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindVideoSessionMemoryKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), videoSessionBindMemoryCount, reinterpret_cast<const VkVideoBindMemoryKHR *>( pVideoSessionBindMemories ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindVideoSessionMemoryKHR( VULKAN_HPP_NAMESPACE::VideoSessionKHR videoSession, ArrayProxy<const VULKAN_HPP_NAMESPACE::VideoBindMemoryKHR> const & videoSessionBindMemories, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindVideoSessionMemoryKHR( m_device, static_cast<VkVideoSessionKHR>( videoSession ), videoSessionBindMemories.size(), reinterpret_cast<const VkVideoBindMemoryKHR *>( videoSessionBindMemories.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindVideoSessionMemoryKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createVideoSessionParametersKHR( const VULKAN_HPP_NAMESPACE::VideoSessionParametersCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR * pVideoSessionParameters, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateVideoSessionParametersKHR( m_device, reinterpret_cast<const VkVideoSessionParametersCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkVideoSessionParametersKHR *>( pVideoSessionParameters ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR >::type Device::createVideoSessionParametersKHR( const VULKAN_HPP_NAMESPACE::VideoSessionParametersCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR  videoSessionParameters;
    Result result = static_cast<Result>( d.vkCreateVideoSessionParametersKHR( m_device, reinterpret_cast<const VkVideoSessionParametersCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkVideoSessionParametersKHR *>( &videoSessionParameters ) ) );
    return createResultValue( result, videoSessionParameters, VULKAN_HPP_NAMESPACE_STRING "::Device::createVideoSessionParametersKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR, Dispatch>>::type Device::createVideoSessionParametersKHRUnique( const VULKAN_HPP_NAMESPACE::VideoSessionParametersCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters;
    Result result = static_cast<Result>( d.vkCreateVideoSessionParametersKHR( m_device, reinterpret_cast<const VkVideoSessionParametersCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkVideoSessionParametersKHR *>( &videoSessionParameters ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR, Dispatch>( result, videoSessionParameters, VULKAN_HPP_NAMESPACE_STRING "::Device::createVideoSessionParametersKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::updateVideoSessionParametersKHR( VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters, const VULKAN_HPP_NAMESPACE::VideoSessionParametersUpdateInfoKHR * pUpdateInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkUpdateVideoSessionParametersKHR( m_device, static_cast<VkVideoSessionParametersKHR>( videoSessionParameters ), reinterpret_cast<const VkVideoSessionParametersUpdateInfoKHR *>( pUpdateInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::updateVideoSessionParametersKHR( VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters, const VULKAN_HPP_NAMESPACE::VideoSessionParametersUpdateInfoKHR & updateInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkUpdateVideoSessionParametersKHR( m_device, static_cast<VkVideoSessionParametersKHR>( videoSessionParameters ), reinterpret_cast<const VkVideoSessionParametersUpdateInfoKHR *>( &updateInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::updateVideoSessionParametersKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyVideoSessionParametersKHR( VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyVideoSessionParametersKHR( m_device, static_cast<VkVideoSessionParametersKHR>( videoSessionParameters ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyVideoSessionParametersKHR( VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyVideoSessionParametersKHR( m_device, static_cast<VkVideoSessionParametersKHR>( videoSessionParameters ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyVideoSessionParametersKHR( m_device, static_cast<VkVideoSessionParametersKHR>( videoSessionParameters ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::VideoSessionParametersKHR videoSessionParameters, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyVideoSessionParametersKHR( m_device, static_cast<VkVideoSessionParametersKHR>( videoSessionParameters ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginVideoCodingKHR( const VULKAN_HPP_NAMESPACE::VideoBeginCodingInfoKHR * pBeginInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginVideoCodingKHR( m_commandBuffer, reinterpret_cast<const VkVideoBeginCodingInfoKHR *>( pBeginInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginVideoCodingKHR( const VULKAN_HPP_NAMESPACE::VideoBeginCodingInfoKHR & beginInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginVideoCodingKHR( m_commandBuffer, reinterpret_cast<const VkVideoBeginCodingInfoKHR *>( &beginInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endVideoCodingKHR( const VULKAN_HPP_NAMESPACE::VideoEndCodingInfoKHR * pEndCodingInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndVideoCodingKHR( m_commandBuffer, reinterpret_cast<const VkVideoEndCodingInfoKHR *>( pEndCodingInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endVideoCodingKHR( const VULKAN_HPP_NAMESPACE::VideoEndCodingInfoKHR & endCodingInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdEndVideoCodingKHR( m_commandBuffer, reinterpret_cast<const VkVideoEndCodingInfoKHR *>( &endCodingInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::controlVideoCodingKHR( const VULKAN_HPP_NAMESPACE::VideoCodingControlInfoKHR * pCodingControlInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdControlVideoCodingKHR( m_commandBuffer, reinterpret_cast<const VkVideoCodingControlInfoKHR *>( pCodingControlInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::controlVideoCodingKHR( const VULKAN_HPP_NAMESPACE::VideoCodingControlInfoKHR & codingControlInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdControlVideoCodingKHR( m_commandBuffer, reinterpret_cast<const VkVideoCodingControlInfoKHR *>( &codingControlInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_KHR_video_decode_queue ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::decodeVideoKHR( const VULKAN_HPP_NAMESPACE::VideoDecodeInfoKHR * pFrameInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDecodeVideoKHR( m_commandBuffer, reinterpret_cast<const VkVideoDecodeInfoKHR *>( pFrameInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::decodeVideoKHR( const VULKAN_HPP_NAMESPACE::VideoDecodeInfoKHR & frameInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdDecodeVideoKHR( m_commandBuffer, reinterpret_cast<const VkVideoDecodeInfoKHR *>( &frameInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_EXT_transform_feedback ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindTransformFeedbackBuffersEXT( uint32_t firstBinding, uint32_t bindingCount, const VULKAN_HPP_NAMESPACE::Buffer * pBuffers, const VULKAN_HPP_NAMESPACE::DeviceSize * pOffsets, const VULKAN_HPP_NAMESPACE::DeviceSize * pSizes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindTransformFeedbackBuffersEXT( m_commandBuffer, firstBinding, bindingCount, reinterpret_cast<const VkBuffer *>( pBuffers ), reinterpret_cast<const VkDeviceSize *>( pOffsets ), reinterpret_cast<const VkDeviceSize *>( pSizes ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindTransformFeedbackBuffersEXT( uint32_t firstBinding, ArrayProxy<const VULKAN_HPP_NAMESPACE::Buffer> const & buffers, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & offsets, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & sizes, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( buffers.size() == offsets.size() );
    VULKAN_HPP_ASSERT( sizes.empty() || buffers.size() == sizes.size() );
#else
    if ( buffers.size() != offsets.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindTransformFeedbackBuffersEXT: buffers.size() != offsets.size()" );
  }
    if ( !sizes.empty() && buffers.size() != sizes.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindTransformFeedbackBuffersEXT: buffers.size() != sizes.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBindTransformFeedbackBuffersEXT( m_commandBuffer, firstBinding, buffers.size(), reinterpret_cast<const VkBuffer *>( buffers.data() ), reinterpret_cast<const VkDeviceSize *>( offsets.data() ), reinterpret_cast<const VkDeviceSize *>( sizes.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginTransformFeedbackEXT( uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VULKAN_HPP_NAMESPACE::Buffer * pCounterBuffers, const VULKAN_HPP_NAMESPACE::DeviceSize * pCounterBufferOffsets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginTransformFeedbackEXT( m_commandBuffer, firstCounterBuffer, counterBufferCount, reinterpret_cast<const VkBuffer *>( pCounterBuffers ), reinterpret_cast<const VkDeviceSize *>( pCounterBufferOffsets ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginTransformFeedbackEXT( uint32_t firstCounterBuffer, ArrayProxy<const VULKAN_HPP_NAMESPACE::Buffer> const & counterBuffers, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & counterBufferOffsets, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( counterBufferOffsets.empty() || counterBuffers.size() == counterBufferOffsets.size() );
#else
    if ( !counterBufferOffsets.empty() && counterBuffers.size() != counterBufferOffsets.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::beginTransformFeedbackEXT: counterBuffers.size() != counterBufferOffsets.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBeginTransformFeedbackEXT( m_commandBuffer, firstCounterBuffer, counterBuffers.size(), reinterpret_cast<const VkBuffer *>( counterBuffers.data() ), reinterpret_cast<const VkDeviceSize *>( counterBufferOffsets.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endTransformFeedbackEXT( uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VULKAN_HPP_NAMESPACE::Buffer * pCounterBuffers, const VULKAN_HPP_NAMESPACE::DeviceSize * pCounterBufferOffsets, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndTransformFeedbackEXT( m_commandBuffer, firstCounterBuffer, counterBufferCount, reinterpret_cast<const VkBuffer *>( pCounterBuffers ), reinterpret_cast<const VkDeviceSize *>( pCounterBufferOffsets ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endTransformFeedbackEXT( uint32_t firstCounterBuffer, ArrayProxy<const VULKAN_HPP_NAMESPACE::Buffer> const & counterBuffers, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & counterBufferOffsets, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( counterBufferOffsets.empty() || counterBuffers.size() == counterBufferOffsets.size() );
#else
    if ( !counterBufferOffsets.empty() && counterBuffers.size() != counterBufferOffsets.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::endTransformFeedbackEXT: counterBuffers.size() != counterBufferOffsets.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdEndTransformFeedbackEXT( m_commandBuffer, firstCounterBuffer, counterBuffers.size(), reinterpret_cast<const VkBuffer *>( counterBuffers.data() ), reinterpret_cast<const VkDeviceSize *>( counterBufferOffsets.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginQueryIndexedEXT( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, VULKAN_HPP_NAMESPACE::QueryControlFlags flags, uint32_t index, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginQueryIndexedEXT( m_commandBuffer, static_cast<VkQueryPool>( queryPool ), query, static_cast<VkQueryControlFlags>( flags ), index );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endQueryIndexedEXT( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, uint32_t index, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndQueryIndexedEXT( m_commandBuffer, static_cast<VkQueryPool>( queryPool ), query, index );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndirectByteCountEXT( uint32_t instanceCount, uint32_t firstInstance, VULKAN_HPP_NAMESPACE::Buffer counterBuffer, VULKAN_HPP_NAMESPACE::DeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndirectByteCountEXT( m_commandBuffer, instanceCount, firstInstance, static_cast<VkBuffer>( counterBuffer ), static_cast<VkDeviceSize>( counterBufferOffset ), counterOffset, vertexStride );
  }

  //=== VK_NVX_binary_import ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createCuModuleNVX( const VULKAN_HPP_NAMESPACE::CuModuleCreateInfoNVX * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::CuModuleNVX * pModule, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateCuModuleNVX( m_device, reinterpret_cast<const VkCuModuleCreateInfoNVX *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkCuModuleNVX *>( pModule ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::CuModuleNVX >::type Device::createCuModuleNVX( const VULKAN_HPP_NAMESPACE::CuModuleCreateInfoNVX & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::CuModuleNVX  module;
    Result result = static_cast<Result>( d.vkCreateCuModuleNVX( m_device, reinterpret_cast<const VkCuModuleCreateInfoNVX *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkCuModuleNVX *>( &module ) ) );
    return createResultValue( result, module, VULKAN_HPP_NAMESPACE_STRING "::Device::createCuModuleNVX" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::CuModuleNVX, Dispatch>>::type Device::createCuModuleNVXUnique( const VULKAN_HPP_NAMESPACE::CuModuleCreateInfoNVX & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::CuModuleNVX module;
    Result result = static_cast<Result>( d.vkCreateCuModuleNVX( m_device, reinterpret_cast<const VkCuModuleCreateInfoNVX *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkCuModuleNVX *>( &module ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::CuModuleNVX, Dispatch>( result, module, VULKAN_HPP_NAMESPACE_STRING "::Device::createCuModuleNVXUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createCuFunctionNVX( const VULKAN_HPP_NAMESPACE::CuFunctionCreateInfoNVX * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::CuFunctionNVX * pFunction, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateCuFunctionNVX( m_device, reinterpret_cast<const VkCuFunctionCreateInfoNVX *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkCuFunctionNVX *>( pFunction ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::CuFunctionNVX >::type Device::createCuFunctionNVX( const VULKAN_HPP_NAMESPACE::CuFunctionCreateInfoNVX & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::CuFunctionNVX  function;
    Result result = static_cast<Result>( d.vkCreateCuFunctionNVX( m_device, reinterpret_cast<const VkCuFunctionCreateInfoNVX *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkCuFunctionNVX *>( &function ) ) );
    return createResultValue( result, function, VULKAN_HPP_NAMESPACE_STRING "::Device::createCuFunctionNVX" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::CuFunctionNVX, Dispatch>>::type Device::createCuFunctionNVXUnique( const VULKAN_HPP_NAMESPACE::CuFunctionCreateInfoNVX & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::CuFunctionNVX function;
    Result result = static_cast<Result>( d.vkCreateCuFunctionNVX( m_device, reinterpret_cast<const VkCuFunctionCreateInfoNVX *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkCuFunctionNVX *>( &function ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::CuFunctionNVX, Dispatch>( result, function, VULKAN_HPP_NAMESPACE_STRING "::Device::createCuFunctionNVXUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyCuModuleNVX( VULKAN_HPP_NAMESPACE::CuModuleNVX module, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyCuModuleNVX( m_device, static_cast<VkCuModuleNVX>( module ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyCuModuleNVX( VULKAN_HPP_NAMESPACE::CuModuleNVX module, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyCuModuleNVX( m_device, static_cast<VkCuModuleNVX>( module ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::CuModuleNVX module, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyCuModuleNVX( m_device, static_cast<VkCuModuleNVX>( module ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::CuModuleNVX module, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyCuModuleNVX( m_device, static_cast<VkCuModuleNVX>( module ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyCuFunctionNVX( VULKAN_HPP_NAMESPACE::CuFunctionNVX function, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyCuFunctionNVX( m_device, static_cast<VkCuFunctionNVX>( function ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyCuFunctionNVX( VULKAN_HPP_NAMESPACE::CuFunctionNVX function, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyCuFunctionNVX( m_device, static_cast<VkCuFunctionNVX>( function ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::CuFunctionNVX function, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyCuFunctionNVX( m_device, static_cast<VkCuFunctionNVX>( function ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::CuFunctionNVX function, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyCuFunctionNVX( m_device, static_cast<VkCuFunctionNVX>( function ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::cuLaunchKernelNVX( const VULKAN_HPP_NAMESPACE::CuLaunchInfoNVX * pLaunchInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCuLaunchKernelNVX( m_commandBuffer, reinterpret_cast<const VkCuLaunchInfoNVX *>( pLaunchInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::cuLaunchKernelNVX( const VULKAN_HPP_NAMESPACE::CuLaunchInfoNVX & launchInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCuLaunchKernelNVX( m_commandBuffer, reinterpret_cast<const VkCuLaunchInfoNVX *>( &launchInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NVX_image_view_handle ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE uint32_t Device::getImageViewHandleNVX( const VULKAN_HPP_NAMESPACE::ImageViewHandleInfoNVX * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetImageViewHandleNVX( m_device, reinterpret_cast<const VkImageViewHandleInfoNVX *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE uint32_t Device::getImageViewHandleNVX( const VULKAN_HPP_NAMESPACE::ImageViewHandleInfoNVX & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetImageViewHandleNVX( m_device, reinterpret_cast<const VkImageViewHandleInfoNVX *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getImageViewAddressNVX( VULKAN_HPP_NAMESPACE::ImageView imageView, VULKAN_HPP_NAMESPACE::ImageViewAddressPropertiesNVX * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetImageViewAddressNVX( m_device, static_cast<VkImageView>( imageView ), reinterpret_cast<VkImageViewAddressPropertiesNVX *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ImageViewAddressPropertiesNVX >::type Device::getImageViewAddressNVX( VULKAN_HPP_NAMESPACE::ImageView imageView, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ImageViewAddressPropertiesNVX  properties;
    Result result = static_cast<Result>( d.vkGetImageViewAddressNVX( m_device, static_cast<VkImageView>( imageView ), reinterpret_cast<VkImageViewAddressPropertiesNVX *>( &properties ) ) );
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING "::Device::getImageViewAddressNVX" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_AMD_draw_indirect_count ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndirectCountAMD( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndirectCountAMD( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndexedIndirectCountAMD( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndexedIndirectCountAMD( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }

  //=== VK_AMD_shader_info ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getShaderInfoAMD( VULKAN_HPP_NAMESPACE::Pipeline pipeline, VULKAN_HPP_NAMESPACE::ShaderStageFlagBits shaderStage, VULKAN_HPP_NAMESPACE::ShaderInfoTypeAMD infoType, size_t * pInfoSize, void * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetShaderInfoAMD( m_device, static_cast<VkPipeline>( pipeline ), static_cast<VkShaderStageFlagBits>( shaderStage ), static_cast<VkShaderInfoTypeAMD>( infoType ), pInfoSize, pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Uint8_tAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<uint8_t, Uint8_tAllocator>>::type Device::getShaderInfoAMD( VULKAN_HPP_NAMESPACE::Pipeline pipeline, VULKAN_HPP_NAMESPACE::ShaderStageFlagBits shaderStage, VULKAN_HPP_NAMESPACE::ShaderInfoTypeAMD infoType, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<uint8_t, Uint8_tAllocator> info;
    size_t infoSize;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetShaderInfoAMD( m_device, static_cast<VkPipeline>( pipeline ), static_cast<VkShaderStageFlagBits>( shaderStage ), static_cast<VkShaderInfoTypeAMD>( infoType ), &infoSize, nullptr ) );
      if ( ( result == Result::eSuccess ) && infoSize )
      {
        info.resize( infoSize );
        result = static_cast<Result>( d.vkGetShaderInfoAMD( m_device, static_cast<VkPipeline>( pipeline ), static_cast<VkShaderStageFlagBits>( shaderStage ), static_cast<VkShaderInfoTypeAMD>( infoType ), &infoSize, reinterpret_cast<void *>( info.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( infoSize <= info.size() );
      if ( infoSize < info.size() )
      {
        info.resize( infoSize );
      }
    }
    return createResultValue( result, info, VULKAN_HPP_NAMESPACE_STRING"::Device::getShaderInfoAMD" );
  }

  template <typename Uint8_tAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, uint8_t>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<uint8_t, Uint8_tAllocator>>::type Device::getShaderInfoAMD( VULKAN_HPP_NAMESPACE::Pipeline pipeline, VULKAN_HPP_NAMESPACE::ShaderStageFlagBits shaderStage, VULKAN_HPP_NAMESPACE::ShaderInfoTypeAMD infoType, Uint8_tAllocator & uint8_tAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<uint8_t, Uint8_tAllocator> info( uint8_tAllocator );
    size_t infoSize;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetShaderInfoAMD( m_device, static_cast<VkPipeline>( pipeline ), static_cast<VkShaderStageFlagBits>( shaderStage ), static_cast<VkShaderInfoTypeAMD>( infoType ), &infoSize, nullptr ) );
      if ( ( result == Result::eSuccess ) && infoSize )
      {
        info.resize( infoSize );
        result = static_cast<Result>( d.vkGetShaderInfoAMD( m_device, static_cast<VkPipeline>( pipeline ), static_cast<VkShaderStageFlagBits>( shaderStage ), static_cast<VkShaderInfoTypeAMD>( infoType ), &infoSize, reinterpret_cast<void *>( info.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( infoSize <= info.size() );
      if ( infoSize < info.size() )
      {
        info.resize( infoSize );
      }
    }
    return createResultValue( result, info, VULKAN_HPP_NAMESPACE_STRING"::Device::getShaderInfoAMD" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_dynamic_rendering ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderingKHR( const VULKAN_HPP_NAMESPACE::RenderingInfo * pRenderingInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginRenderingKHR( m_commandBuffer, reinterpret_cast<const VkRenderingInfo *>( pRenderingInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderingKHR( const VULKAN_HPP_NAMESPACE::RenderingInfo & renderingInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginRenderingKHR( m_commandBuffer, reinterpret_cast<const VkRenderingInfo *>( &renderingInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRenderingKHR( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndRenderingKHR( m_commandBuffer );
  }

#if defined( VK_USE_PLATFORM_GGP )
  //=== VK_GGP_stream_descriptor_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createStreamDescriptorSurfaceGGP( const VULKAN_HPP_NAMESPACE::StreamDescriptorSurfaceCreateInfoGGP * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateStreamDescriptorSurfaceGGP( m_instance, reinterpret_cast<const VkStreamDescriptorSurfaceCreateInfoGGP *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createStreamDescriptorSurfaceGGP( const VULKAN_HPP_NAMESPACE::StreamDescriptorSurfaceCreateInfoGGP & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateStreamDescriptorSurfaceGGP( m_instance, reinterpret_cast<const VkStreamDescriptorSurfaceCreateInfoGGP *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createStreamDescriptorSurfaceGGP" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createStreamDescriptorSurfaceGGPUnique( const VULKAN_HPP_NAMESPACE::StreamDescriptorSurfaceCreateInfoGGP & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateStreamDescriptorSurfaceGGP( m_instance, reinterpret_cast<const VkStreamDescriptorSurfaceCreateInfoGGP *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createStreamDescriptorSurfaceGGPUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_GGP*/

  //=== VK_NV_external_memory_capabilities ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getExternalImageFormatPropertiesNV( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::ImageTiling tiling, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageCreateFlags flags, VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagsNV externalHandleType, VULKAN_HPP_NAMESPACE::ExternalImageFormatPropertiesNV * pExternalImageFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceExternalImageFormatPropertiesNV( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkImageTiling>( tiling ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageCreateFlags>( flags ), static_cast<VkExternalMemoryHandleTypeFlagsNV>( externalHandleType ), reinterpret_cast<VkExternalImageFormatPropertiesNV *>( pExternalImageFormatProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ExternalImageFormatPropertiesNV >::type PhysicalDevice::getExternalImageFormatPropertiesNV( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::ImageType type, VULKAN_HPP_NAMESPACE::ImageTiling tiling, VULKAN_HPP_NAMESPACE::ImageUsageFlags usage, VULKAN_HPP_NAMESPACE::ImageCreateFlags flags, VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagsNV externalHandleType, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalImageFormatPropertiesNV  externalImageFormatProperties;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceExternalImageFormatPropertiesNV( m_physicalDevice, static_cast<VkFormat>( format ), static_cast<VkImageType>( type ), static_cast<VkImageTiling>( tiling ), static_cast<VkImageUsageFlags>( usage ), static_cast<VkImageCreateFlags>( flags ), static_cast<VkExternalMemoryHandleTypeFlagsNV>( externalHandleType ), reinterpret_cast<VkExternalImageFormatPropertiesNV *>( &externalImageFormatProperties ) ) );
    return createResultValue( result, externalImageFormatProperties, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getExternalImageFormatPropertiesNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_external_memory_win32 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryWin32HandleNV( VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagsNV handleType, HANDLE * pHandle, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryWin32HandleNV( m_device, static_cast<VkDeviceMemory>( memory ), static_cast<VkExternalMemoryHandleTypeFlagsNV>( handleType ), pHandle ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<HANDLE >::type Device::getMemoryWin32HandleNV( VULKAN_HPP_NAMESPACE::DeviceMemory memory, VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagsNV handleType, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    HANDLE  handle;
    Result result = static_cast<Result>( d.vkGetMemoryWin32HandleNV( m_device, static_cast<VkDeviceMemory>( memory ), static_cast<VkExternalMemoryHandleTypeFlagsNV>( handleType ), &handle ) );
    return createResultValue( result, handle, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryWin32HandleNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_get_physical_device_properties2 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getFeatures2KHR( VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2 * pFeatures, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceFeatures2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures2 *>( pFeatures ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2  PhysicalDevice::getFeatures2KHR( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2  features;
    d.vkGetPhysicalDeviceFeatures2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures2 *>( &features ) );
    return features;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getFeatures2KHR( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2 & features = structureChain.template get<VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures2>();
    d.vkGetPhysicalDeviceFeatures2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceFeatures2 *>( &features ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getProperties2KHR( VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2 * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceProperties2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties2 *>( pProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2  PhysicalDevice::getProperties2KHR( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2  properties;
    d.vkGetPhysicalDeviceProperties2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties2 *>( &properties ) );
    return properties;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getProperties2KHR( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2 & properties = structureChain.template get<VULKAN_HPP_NAMESPACE::PhysicalDeviceProperties2>();
    d.vkGetPhysicalDeviceProperties2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceProperties2 *>( &properties ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getFormatProperties2KHR( VULKAN_HPP_NAMESPACE::Format format, VULKAN_HPP_NAMESPACE::FormatProperties2 * pFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceFormatProperties2KHR( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties2 *>( pFormatProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::FormatProperties2  PhysicalDevice::getFormatProperties2KHR( VULKAN_HPP_NAMESPACE::Format format, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::FormatProperties2  formatProperties;
    d.vkGetPhysicalDeviceFormatProperties2KHR( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties2 *>( &formatProperties ) );
    return formatProperties;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getFormatProperties2KHR( VULKAN_HPP_NAMESPACE::Format format, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::FormatProperties2 & formatProperties = structureChain.template get<VULKAN_HPP_NAMESPACE::FormatProperties2>();
    d.vkGetPhysicalDeviceFormatProperties2KHR( m_physicalDevice, static_cast<VkFormat>( format ), reinterpret_cast<VkFormatProperties2 *>( &formatProperties ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getImageFormatProperties2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceImageFormatInfo2 * pImageFormatInfo, VULKAN_HPP_NAMESPACE::ImageFormatProperties2 * pImageFormatProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2 *>( pImageFormatInfo ), reinterpret_cast<VkImageFormatProperties2 *>( pImageFormatProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ImageFormatProperties2 >::type PhysicalDevice::getImageFormatProperties2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceImageFormatInfo2 & imageFormatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ImageFormatProperties2  imageFormatProperties;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2 *>( &imageFormatInfo ), reinterpret_cast<VkImageFormatProperties2 *>( &imageFormatProperties ) ) );
    return createResultValue( result, imageFormatProperties, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getImageFormatProperties2KHR" );
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<StructureChain<X, Y, Z...>>::type PhysicalDevice::getImageFormatProperties2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceImageFormatInfo2 & imageFormatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::ImageFormatProperties2 & imageFormatProperties = structureChain.template get<VULKAN_HPP_NAMESPACE::ImageFormatProperties2>();
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2 *>( &imageFormatInfo ), reinterpret_cast<VkImageFormatProperties2 *>( &imageFormatProperties ) ) );
    return createResultValue( result, structureChain, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getImageFormatProperties2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getQueueFamilyProperties2KHR( uint32_t * pQueueFamilyPropertyCount, VULKAN_HPP_NAMESPACE::QueueFamilyProperties2 * pQueueFamilyProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, pQueueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( pQueueFamilyProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename QueueFamilyProperties2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> PhysicalDevice::getQueueFamilyProperties2KHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> queueFamilyProperties;
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    queueFamilyProperties.resize( queueFamilyPropertyCount );
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    return queueFamilyProperties;
  }

  template <typename QueueFamilyProperties2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, QueueFamilyProperties2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> PhysicalDevice::getQueueFamilyProperties2KHR( QueueFamilyProperties2Allocator & queueFamilyProperties2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<QueueFamilyProperties2, QueueFamilyProperties2Allocator> queueFamilyProperties( queueFamilyProperties2Allocator );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    queueFamilyProperties.resize( queueFamilyPropertyCount );
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    return queueFamilyProperties;
  }

  template <typename StructureChain, typename StructureChainAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<StructureChain, StructureChainAllocator> PhysicalDevice::getQueueFamilyProperties2KHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    std::vector<StructureChain, StructureChainAllocator> returnVector( queueFamilyPropertyCount );
    std::vector<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2> queueFamilyProperties( queueFamilyPropertyCount );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      queueFamilyProperties[i].pNext =
        returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>().pNext;
    }
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>() = queueFamilyProperties[i];
    }
    return returnVector;
  }

  template <typename StructureChain, typename StructureChainAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, StructureChain>::value, int>::type>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<StructureChain, StructureChainAllocator> PhysicalDevice::getQueueFamilyProperties2KHR( StructureChainAllocator & structureChainAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    uint32_t queueFamilyPropertyCount;
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, nullptr );
    std::vector<StructureChain, StructureChainAllocator> returnVector( queueFamilyPropertyCount, structureChainAllocator );
    std::vector<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2> queueFamilyProperties( queueFamilyPropertyCount );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      queueFamilyProperties[i].pNext =
        returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>().pNext;
    }
    d.vkGetPhysicalDeviceQueueFamilyProperties2KHR( m_physicalDevice, &queueFamilyPropertyCount, reinterpret_cast<VkQueueFamilyProperties2 *>( queueFamilyProperties.data() ) );
    VULKAN_HPP_ASSERT( queueFamilyPropertyCount <= queueFamilyProperties.size() );
    for ( uint32_t i = 0; i < queueFamilyPropertyCount; i++ )
    {
      returnVector[i].template get<VULKAN_HPP_NAMESPACE::QueueFamilyProperties2>() = queueFamilyProperties[i];
    }
    return returnVector;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getMemoryProperties2KHR( VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2 * pMemoryProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceMemoryProperties2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties2 *>( pMemoryProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2  PhysicalDevice::getMemoryProperties2KHR( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2  memoryProperties;
    d.vkGetPhysicalDeviceMemoryProperties2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties2 *>( &memoryProperties ) );
    return memoryProperties;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> PhysicalDevice::getMemoryProperties2KHR( Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2 & memoryProperties = structureChain.template get<VULKAN_HPP_NAMESPACE::PhysicalDeviceMemoryProperties2>();
    d.vkGetPhysicalDeviceMemoryProperties2KHR( m_physicalDevice, reinterpret_cast<VkPhysicalDeviceMemoryProperties2 *>( &memoryProperties ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getSparseImageFormatProperties2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSparseImageFormatInfo2 * pFormatInfo, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::SparseImageFormatProperties2 * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceSparseImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( pFormatInfo ), pPropertyCount, reinterpret_cast<VkSparseImageFormatProperties2 *>( pProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageFormatProperties2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> PhysicalDevice::getSparseImageFormatProperties2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSparseImageFormatInfo2 & formatInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> properties;
    uint32_t propertyCount;
    d.vkGetPhysicalDeviceSparseImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, nullptr );
    properties.resize( propertyCount );
    d.vkGetPhysicalDeviceSparseImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, reinterpret_cast<VkSparseImageFormatProperties2 *>( properties.data() ) );
    VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
    return properties;
  }

  template <typename SparseImageFormatProperties2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageFormatProperties2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> PhysicalDevice::getSparseImageFormatProperties2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSparseImageFormatInfo2 & formatInfo, SparseImageFormatProperties2Allocator & sparseImageFormatProperties2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageFormatProperties2, SparseImageFormatProperties2Allocator> properties( sparseImageFormatProperties2Allocator );
    uint32_t propertyCount;
    d.vkGetPhysicalDeviceSparseImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, nullptr );
    properties.resize( propertyCount );
    d.vkGetPhysicalDeviceSparseImageFormatProperties2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2 *>( &formatInfo ), &propertyCount, reinterpret_cast<VkSparseImageFormatProperties2 *>( properties.data() ) );
    VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
    return properties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_device_group ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getGroupPeerMemoryFeaturesKHR( uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VULKAN_HPP_NAMESPACE::PeerMemoryFeatureFlags * pPeerMemoryFeatures, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceGroupPeerMemoryFeaturesKHR( m_device, heapIndex, localDeviceIndex, remoteDeviceIndex, reinterpret_cast<VkPeerMemoryFeatureFlags *>( pPeerMemoryFeatures ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::PeerMemoryFeatureFlags  Device::getGroupPeerMemoryFeaturesKHR( uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PeerMemoryFeatureFlags  peerMemoryFeatures;
    d.vkGetDeviceGroupPeerMemoryFeaturesKHR( m_device, heapIndex, localDeviceIndex, remoteDeviceIndex, reinterpret_cast<VkPeerMemoryFeatureFlags *>( &peerMemoryFeatures ) );
    return peerMemoryFeatures;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDeviceMaskKHR( uint32_t deviceMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDeviceMaskKHR( m_commandBuffer, deviceMask );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::dispatchBaseKHR( uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDispatchBaseKHR( m_commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ );
  }

#if defined( VK_USE_PLATFORM_VI_NN )
  //=== VK_NN_vi_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createViSurfaceNN( const VULKAN_HPP_NAMESPACE::ViSurfaceCreateInfoNN * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateViSurfaceNN( m_instance, reinterpret_cast<const VkViSurfaceCreateInfoNN *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createViSurfaceNN( const VULKAN_HPP_NAMESPACE::ViSurfaceCreateInfoNN & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateViSurfaceNN( m_instance, reinterpret_cast<const VkViSurfaceCreateInfoNN *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createViSurfaceNN" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createViSurfaceNNUnique( const VULKAN_HPP_NAMESPACE::ViSurfaceCreateInfoNN & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateViSurfaceNN( m_instance, reinterpret_cast<const VkViSurfaceCreateInfoNN *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createViSurfaceNNUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_VI_NN*/

  //=== VK_KHR_maintenance1 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::trimCommandPoolKHR( VULKAN_HPP_NAMESPACE::CommandPool commandPool, VULKAN_HPP_NAMESPACE::CommandPoolTrimFlags flags, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkTrimCommandPoolKHR( m_device, static_cast<VkCommandPool>( commandPool ), static_cast<VkCommandPoolTrimFlags>( flags ) );
  }

  //=== VK_KHR_device_group_creation ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::enumeratePhysicalDeviceGroupsKHR( uint32_t * pPhysicalDeviceGroupCount, VULKAN_HPP_NAMESPACE::PhysicalDeviceGroupProperties * pPhysicalDeviceGroupProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumeratePhysicalDeviceGroupsKHR( m_instance, pPhysicalDeviceGroupCount, reinterpret_cast<VkPhysicalDeviceGroupProperties *>( pPhysicalDeviceGroupProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PhysicalDeviceGroupPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator>>::type Instance::enumeratePhysicalDeviceGroupsKHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator> physicalDeviceGroupProperties;
    uint32_t physicalDeviceGroupCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroupsKHR( m_instance, &physicalDeviceGroupCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && physicalDeviceGroupCount )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroupsKHR( m_instance, &physicalDeviceGroupCount, reinterpret_cast<VkPhysicalDeviceGroupProperties *>( physicalDeviceGroupProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( physicalDeviceGroupCount <= physicalDeviceGroupProperties.size() );
      if ( physicalDeviceGroupCount < physicalDeviceGroupProperties.size() )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
      }
    }
    return createResultValue( result, physicalDeviceGroupProperties, VULKAN_HPP_NAMESPACE_STRING"::Instance::enumeratePhysicalDeviceGroupsKHR" );
  }

  template <typename PhysicalDeviceGroupPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PhysicalDeviceGroupProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator>>::type Instance::enumeratePhysicalDeviceGroupsKHR( PhysicalDeviceGroupPropertiesAllocator & physicalDeviceGroupPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceGroupProperties, PhysicalDeviceGroupPropertiesAllocator> physicalDeviceGroupProperties( physicalDeviceGroupPropertiesAllocator );
    uint32_t physicalDeviceGroupCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroupsKHR( m_instance, &physicalDeviceGroupCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && physicalDeviceGroupCount )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDeviceGroupsKHR( m_instance, &physicalDeviceGroupCount, reinterpret_cast<VkPhysicalDeviceGroupProperties *>( physicalDeviceGroupProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( physicalDeviceGroupCount <= physicalDeviceGroupProperties.size() );
      if ( physicalDeviceGroupCount < physicalDeviceGroupProperties.size() )
      {
        physicalDeviceGroupProperties.resize( physicalDeviceGroupCount );
      }
    }
    return createResultValue( result, physicalDeviceGroupProperties, VULKAN_HPP_NAMESPACE_STRING"::Instance::enumeratePhysicalDeviceGroupsKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_external_memory_capabilities ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getExternalBufferPropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalBufferInfo * pExternalBufferInfo, VULKAN_HPP_NAMESPACE::ExternalBufferProperties * pExternalBufferProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceExternalBufferPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo *>( pExternalBufferInfo ), reinterpret_cast<VkExternalBufferProperties *>( pExternalBufferProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::ExternalBufferProperties  PhysicalDevice::getExternalBufferPropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalBufferInfo & externalBufferInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalBufferProperties  externalBufferProperties;
    d.vkGetPhysicalDeviceExternalBufferPropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo *>( &externalBufferInfo ), reinterpret_cast<VkExternalBufferProperties *>( &externalBufferProperties ) );
    return externalBufferProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_memory_win32 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryWin32HandleKHR( const VULKAN_HPP_NAMESPACE::MemoryGetWin32HandleInfoKHR * pGetWin32HandleInfo, HANDLE * pHandle, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryWin32HandleKHR( m_device, reinterpret_cast<const VkMemoryGetWin32HandleInfoKHR *>( pGetWin32HandleInfo ), pHandle ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<HANDLE >::type Device::getMemoryWin32HandleKHR( const VULKAN_HPP_NAMESPACE::MemoryGetWin32HandleInfoKHR & getWin32HandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    HANDLE  handle;
    Result result = static_cast<Result>( d.vkGetMemoryWin32HandleKHR( m_device, reinterpret_cast<const VkMemoryGetWin32HandleInfoKHR *>( &getWin32HandleInfo ), &handle ) );
    return createResultValue( result, handle, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryWin32HandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryWin32HandlePropertiesKHR( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VULKAN_HPP_NAMESPACE::MemoryWin32HandlePropertiesKHR * pMemoryWin32HandleProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryWin32HandlePropertiesKHR( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), handle, reinterpret_cast<VkMemoryWin32HandlePropertiesKHR *>( pMemoryWin32HandleProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::MemoryWin32HandlePropertiesKHR >::type Device::getMemoryWin32HandlePropertiesKHR( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryWin32HandlePropertiesKHR  memoryWin32HandleProperties;
    Result result = static_cast<Result>( d.vkGetMemoryWin32HandlePropertiesKHR( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), handle, reinterpret_cast<VkMemoryWin32HandlePropertiesKHR *>( &memoryWin32HandleProperties ) ) );
    return createResultValue( result, memoryWin32HandleProperties, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryWin32HandlePropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_memory_fd ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryFdKHR( const VULKAN_HPP_NAMESPACE::MemoryGetFdInfoKHR * pGetFdInfo, int * pFd, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryFdKHR( m_device, reinterpret_cast<const VkMemoryGetFdInfoKHR *>( pGetFdInfo ), pFd ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<int >::type Device::getMemoryFdKHR( const VULKAN_HPP_NAMESPACE::MemoryGetFdInfoKHR & getFdInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    int  fd;
    Result result = static_cast<Result>( d.vkGetMemoryFdKHR( m_device, reinterpret_cast<const VkMemoryGetFdInfoKHR *>( &getFdInfo ), &fd ) );
    return createResultValue( result, fd, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryFdKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryFdPropertiesKHR( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, int fd, VULKAN_HPP_NAMESPACE::MemoryFdPropertiesKHR * pMemoryFdProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryFdPropertiesKHR( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), fd, reinterpret_cast<VkMemoryFdPropertiesKHR *>( pMemoryFdProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::MemoryFdPropertiesKHR >::type Device::getMemoryFdPropertiesKHR( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, int fd, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryFdPropertiesKHR  memoryFdProperties;
    Result result = static_cast<Result>( d.vkGetMemoryFdPropertiesKHR( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), fd, reinterpret_cast<VkMemoryFdPropertiesKHR *>( &memoryFdProperties ) ) );
    return createResultValue( result, memoryFdProperties, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryFdPropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_external_semaphore_capabilities ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getExternalSemaphorePropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo, VULKAN_HPP_NAMESPACE::ExternalSemaphoreProperties * pExternalSemaphoreProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceExternalSemaphorePropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo *>( pExternalSemaphoreInfo ), reinterpret_cast<VkExternalSemaphoreProperties *>( pExternalSemaphoreProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::ExternalSemaphoreProperties  PhysicalDevice::getExternalSemaphorePropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalSemaphoreInfo & externalSemaphoreInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalSemaphoreProperties  externalSemaphoreProperties;
    d.vkGetPhysicalDeviceExternalSemaphorePropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo *>( &externalSemaphoreInfo ), reinterpret_cast<VkExternalSemaphoreProperties *>( &externalSemaphoreProperties ) );
    return externalSemaphoreProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_semaphore_win32 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::importSemaphoreWin32HandleKHR( const VULKAN_HPP_NAMESPACE::ImportSemaphoreWin32HandleInfoKHR * pImportSemaphoreWin32HandleInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkImportSemaphoreWin32HandleKHR( m_device, reinterpret_cast<const VkImportSemaphoreWin32HandleInfoKHR *>( pImportSemaphoreWin32HandleInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::importSemaphoreWin32HandleKHR( const VULKAN_HPP_NAMESPACE::ImportSemaphoreWin32HandleInfoKHR & importSemaphoreWin32HandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkImportSemaphoreWin32HandleKHR( m_device, reinterpret_cast<const VkImportSemaphoreWin32HandleInfoKHR *>( &importSemaphoreWin32HandleInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::importSemaphoreWin32HandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSemaphoreWin32HandleKHR( const VULKAN_HPP_NAMESPACE::SemaphoreGetWin32HandleInfoKHR * pGetWin32HandleInfo, HANDLE * pHandle, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSemaphoreWin32HandleKHR( m_device, reinterpret_cast<const VkSemaphoreGetWin32HandleInfoKHR *>( pGetWin32HandleInfo ), pHandle ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<HANDLE >::type Device::getSemaphoreWin32HandleKHR( const VULKAN_HPP_NAMESPACE::SemaphoreGetWin32HandleInfoKHR & getWin32HandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    HANDLE  handle;
    Result result = static_cast<Result>( d.vkGetSemaphoreWin32HandleKHR( m_device, reinterpret_cast<const VkSemaphoreGetWin32HandleInfoKHR *>( &getWin32HandleInfo ), &handle ) );
    return createResultValue( result, handle, VULKAN_HPP_NAMESPACE_STRING "::Device::getSemaphoreWin32HandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_semaphore_fd ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::importSemaphoreFdKHR( const VULKAN_HPP_NAMESPACE::ImportSemaphoreFdInfoKHR * pImportSemaphoreFdInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkImportSemaphoreFdKHR( m_device, reinterpret_cast<const VkImportSemaphoreFdInfoKHR *>( pImportSemaphoreFdInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::importSemaphoreFdKHR( const VULKAN_HPP_NAMESPACE::ImportSemaphoreFdInfoKHR & importSemaphoreFdInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkImportSemaphoreFdKHR( m_device, reinterpret_cast<const VkImportSemaphoreFdInfoKHR *>( &importSemaphoreFdInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::importSemaphoreFdKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSemaphoreFdKHR( const VULKAN_HPP_NAMESPACE::SemaphoreGetFdInfoKHR * pGetFdInfo, int * pFd, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSemaphoreFdKHR( m_device, reinterpret_cast<const VkSemaphoreGetFdInfoKHR *>( pGetFdInfo ), pFd ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<int >::type Device::getSemaphoreFdKHR( const VULKAN_HPP_NAMESPACE::SemaphoreGetFdInfoKHR & getFdInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    int  fd;
    Result result = static_cast<Result>( d.vkGetSemaphoreFdKHR( m_device, reinterpret_cast<const VkSemaphoreGetFdInfoKHR *>( &getFdInfo ), &fd ) );
    return createResultValue( result, fd, VULKAN_HPP_NAMESPACE_STRING "::Device::getSemaphoreFdKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_push_descriptor ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pushDescriptorSetKHR( VULKAN_HPP_NAMESPACE::PipelineBindPoint pipelineBindPoint, VULKAN_HPP_NAMESPACE::PipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VULKAN_HPP_NAMESPACE::WriteDescriptorSet * pDescriptorWrites, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPushDescriptorSetKHR( m_commandBuffer, static_cast<VkPipelineBindPoint>( pipelineBindPoint ), static_cast<VkPipelineLayout>( layout ), set, descriptorWriteCount, reinterpret_cast<const VkWriteDescriptorSet *>( pDescriptorWrites ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pushDescriptorSetKHR( VULKAN_HPP_NAMESPACE::PipelineBindPoint pipelineBindPoint, VULKAN_HPP_NAMESPACE::PipelineLayout layout, uint32_t set, ArrayProxy<const VULKAN_HPP_NAMESPACE::WriteDescriptorSet> const & descriptorWrites, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPushDescriptorSetKHR( m_commandBuffer, static_cast<VkPipelineBindPoint>( pipelineBindPoint ), static_cast<VkPipelineLayout>( layout ), set, descriptorWrites.size(), reinterpret_cast<const VkWriteDescriptorSet *>( descriptorWrites.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pushDescriptorSetWithTemplateKHR( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, VULKAN_HPP_NAMESPACE::PipelineLayout layout, uint32_t set, const void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPushDescriptorSetWithTemplateKHR( m_commandBuffer, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), static_cast<VkPipelineLayout>( layout ), set, pData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pushDescriptorSetWithTemplateKHR( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, VULKAN_HPP_NAMESPACE::PipelineLayout layout, uint32_t set, DataType const & data, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPushDescriptorSetWithTemplateKHR( m_commandBuffer, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), static_cast<VkPipelineLayout>( layout ), set, reinterpret_cast<const void *>( &data ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_conditional_rendering ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginConditionalRenderingEXT( const VULKAN_HPP_NAMESPACE::ConditionalRenderingBeginInfoEXT * pConditionalRenderingBegin, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginConditionalRenderingEXT( m_commandBuffer, reinterpret_cast<const VkConditionalRenderingBeginInfoEXT *>( pConditionalRenderingBegin ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginConditionalRenderingEXT( const VULKAN_HPP_NAMESPACE::ConditionalRenderingBeginInfoEXT & conditionalRenderingBegin, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginConditionalRenderingEXT( m_commandBuffer, reinterpret_cast<const VkConditionalRenderingBeginInfoEXT *>( &conditionalRenderingBegin ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endConditionalRenderingEXT( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndConditionalRenderingEXT( m_commandBuffer );
  }

  //=== VK_KHR_descriptor_update_template ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createDescriptorUpdateTemplateKHR( const VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplateCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate * pDescriptorUpdateTemplate, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDescriptorUpdateTemplateKHR( m_device, reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDescriptorUpdateTemplate *>( pDescriptorUpdateTemplate ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate >::type Device::createDescriptorUpdateTemplateKHR( const VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplateCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate  descriptorUpdateTemplate;
    Result result = static_cast<Result>( d.vkCreateDescriptorUpdateTemplateKHR( m_device, reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorUpdateTemplate *>( &descriptorUpdateTemplate ) ) );
    return createResultValue( result, descriptorUpdateTemplate, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorUpdateTemplateKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate, Dispatch>>::type Device::createDescriptorUpdateTemplateKHRUnique( const VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplateCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate;
    Result result = static_cast<Result>( d.vkCreateDescriptorUpdateTemplateKHR( m_device, reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDescriptorUpdateTemplate *>( &descriptorUpdateTemplate ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate, Dispatch>( result, descriptorUpdateTemplate, VULKAN_HPP_NAMESPACE_STRING "::Device::createDescriptorUpdateTemplateKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorUpdateTemplateKHR( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDescriptorUpdateTemplateKHR( m_device, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDescriptorUpdateTemplateKHR( VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDescriptorUpdateTemplateKHR( m_device, static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::updateDescriptorSetWithTemplateKHR( VULKAN_HPP_NAMESPACE::DescriptorSet descriptorSet, VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, const void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkUpdateDescriptorSetWithTemplateKHR( m_device, static_cast<VkDescriptorSet>( descriptorSet ), static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), pData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Dispatch>
  VULKAN_HPP_INLINE void Device::updateDescriptorSetWithTemplateKHR( VULKAN_HPP_NAMESPACE::DescriptorSet descriptorSet, VULKAN_HPP_NAMESPACE::DescriptorUpdateTemplate descriptorUpdateTemplate, DataType const & data, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkUpdateDescriptorSetWithTemplateKHR( m_device, static_cast<VkDescriptorSet>( descriptorSet ), static_cast<VkDescriptorUpdateTemplate>( descriptorUpdateTemplate ), reinterpret_cast<const void *>( &data ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_clip_space_w_scaling ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportWScalingNV( uint32_t firstViewport, uint32_t viewportCount, const VULKAN_HPP_NAMESPACE::ViewportWScalingNV * pViewportWScalings, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetViewportWScalingNV( m_commandBuffer, firstViewport, viewportCount, reinterpret_cast<const VkViewportWScalingNV *>( pViewportWScalings ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportWScalingNV( uint32_t firstViewport, ArrayProxy<const VULKAN_HPP_NAMESPACE::ViewportWScalingNV> const & viewportWScalings, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetViewportWScalingNV( m_commandBuffer, firstViewport, viewportWScalings.size(), reinterpret_cast<const VkViewportWScalingNV *>( viewportWScalings.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_direct_mode_display ===


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Result PhysicalDevice::releaseDisplayEXT( VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkReleaseDisplayEXT( m_physicalDevice, static_cast<VkDisplayKHR>( display ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type PhysicalDevice::releaseDisplayEXT( VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkReleaseDisplayEXT( m_physicalDevice, static_cast<VkDisplayKHR>( display ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::releaseDisplayEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_XLIB_XRANDR_EXT )
  //=== VK_EXT_acquire_xlib_display ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::acquireXlibDisplayEXT( Display * dpy, VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireXlibDisplayEXT( m_physicalDevice, dpy, static_cast<VkDisplayKHR>( display ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type PhysicalDevice::acquireXlibDisplayEXT( Display & dpy, VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkAcquireXlibDisplayEXT( m_physicalDevice, &dpy, static_cast<VkDisplayKHR>( display ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::acquireXlibDisplayEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getRandROutputDisplayEXT( Display * dpy, RROutput rrOutput, VULKAN_HPP_NAMESPACE::DisplayKHR * pDisplay, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetRandROutputDisplayEXT( m_physicalDevice, dpy, rrOutput, reinterpret_cast<VkDisplayKHR *>( pDisplay ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DisplayKHR >::type PhysicalDevice::getRandROutputDisplayEXT( Display & dpy, RROutput rrOutput, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DisplayKHR  display;
    Result result = static_cast<Result>( d.vkGetRandROutputDisplayEXT( m_physicalDevice, &dpy, rrOutput, reinterpret_cast<VkDisplayKHR *>( &display ) ) );
    return createResultValue( result, display, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getRandROutputDisplayEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DisplayKHR, Dispatch>>::type PhysicalDevice::getRandROutputDisplayEXTUnique( Display & dpy, RROutput rrOutput, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DisplayKHR display;
    Result result = static_cast<Result>( d.vkGetRandROutputDisplayEXT( m_physicalDevice, &dpy, rrOutput, reinterpret_cast<VkDisplayKHR *>( &display ) ) );
    ObjectRelease<PhysicalDevice, Dispatch> deleter( *this, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DisplayKHR, Dispatch>( result, display, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getRandROutputDisplayEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_XLIB_XRANDR_EXT*/

  //=== VK_EXT_display_surface_counter ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfaceCapabilities2EXT( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, VULKAN_HPP_NAMESPACE::SurfaceCapabilities2EXT * pSurfaceCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilities2EXT( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkSurfaceCapabilities2EXT *>( pSurfaceCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceCapabilities2EXT >::type PhysicalDevice::getSurfaceCapabilities2EXT( VULKAN_HPP_NAMESPACE::SurfaceKHR surface, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceCapabilities2EXT  surfaceCapabilities;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilities2EXT( m_physicalDevice, static_cast<VkSurfaceKHR>( surface ), reinterpret_cast<VkSurfaceCapabilities2EXT *>( &surfaceCapabilities ) ) );
    return createResultValue( result, surfaceCapabilities, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getSurfaceCapabilities2EXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_display_control ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::displayPowerControlEXT( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayPowerInfoEXT * pDisplayPowerInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkDisplayPowerControlEXT( m_device, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayPowerInfoEXT *>( pDisplayPowerInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::displayPowerControlEXT( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayPowerInfoEXT & displayPowerInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkDisplayPowerControlEXT( m_device, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayPowerInfoEXT *>( &displayPowerInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::displayPowerControlEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::registerEventEXT( const VULKAN_HPP_NAMESPACE::DeviceEventInfoEXT * pDeviceEventInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Fence * pFence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkRegisterDeviceEventEXT( m_device, reinterpret_cast<const VkDeviceEventInfoEXT *>( pDeviceEventInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkFence *>( pFence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Fence >::type Device::registerEventEXT( const VULKAN_HPP_NAMESPACE::DeviceEventInfoEXT & deviceEventInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Fence  fence;
    Result result = static_cast<Result>( d.vkRegisterDeviceEventEXT( m_device, reinterpret_cast<const VkDeviceEventInfoEXT *>( &deviceEventInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFence *>( &fence ) ) );
    return createResultValue( result, fence, VULKAN_HPP_NAMESPACE_STRING "::Device::registerEventEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Fence, Dispatch>>::type Device::registerEventEXTUnique( const VULKAN_HPP_NAMESPACE::DeviceEventInfoEXT & deviceEventInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Fence fence;
    Result result = static_cast<Result>( d.vkRegisterDeviceEventEXT( m_device, reinterpret_cast<const VkDeviceEventInfoEXT *>( &deviceEventInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFence *>( &fence ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Fence, Dispatch>( result, fence, VULKAN_HPP_NAMESPACE_STRING "::Device::registerEventEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::registerDisplayEventEXT( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayEventInfoEXT * pDisplayEventInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Fence * pFence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkRegisterDisplayEventEXT( m_device, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayEventInfoEXT *>( pDisplayEventInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkFence *>( pFence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::Fence >::type Device::registerDisplayEventEXT( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayEventInfoEXT & displayEventInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Fence  fence;
    Result result = static_cast<Result>( d.vkRegisterDisplayEventEXT( m_device, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayEventInfoEXT *>( &displayEventInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFence *>( &fence ) ) );
    return createResultValue( result, fence, VULKAN_HPP_NAMESPACE_STRING "::Device::registerDisplayEventEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::Fence, Dispatch>>::type Device::registerDisplayEventEXTUnique( VULKAN_HPP_NAMESPACE::DisplayKHR display, const VULKAN_HPP_NAMESPACE::DisplayEventInfoEXT & displayEventInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::Fence fence;
    Result result = static_cast<Result>( d.vkRegisterDisplayEventEXT( m_device, static_cast<VkDisplayKHR>( display ), reinterpret_cast<const VkDisplayEventInfoEXT *>( &displayEventInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkFence *>( &fence ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::Fence, Dispatch>( result, fence, VULKAN_HPP_NAMESPACE_STRING "::Device::registerDisplayEventEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSwapchainCounterEXT( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, VULKAN_HPP_NAMESPACE::SurfaceCounterFlagBitsEXT counter, uint64_t * pCounterValue, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSwapchainCounterEXT( m_device, static_cast<VkSwapchainKHR>( swapchain ), static_cast<VkSurfaceCounterFlagBitsEXT>( counter ), pCounterValue ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<uint64_t >::type Device::getSwapchainCounterEXT( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, VULKAN_HPP_NAMESPACE::SurfaceCounterFlagBitsEXT counter, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint64_t  counterValue;
    Result result = static_cast<Result>( d.vkGetSwapchainCounterEXT( m_device, static_cast<VkSwapchainKHR>( swapchain ), static_cast<VkSurfaceCounterFlagBitsEXT>( counter ), &counterValue ) );
    return createResultValue( result, counterValue, VULKAN_HPP_NAMESPACE_STRING "::Device::getSwapchainCounterEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_GOOGLE_display_timing ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getRefreshCycleDurationGOOGLE( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, VULKAN_HPP_NAMESPACE::RefreshCycleDurationGOOGLE * pDisplayTimingProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetRefreshCycleDurationGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), reinterpret_cast<VkRefreshCycleDurationGOOGLE *>( pDisplayTimingProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::RefreshCycleDurationGOOGLE >::type Device::getRefreshCycleDurationGOOGLE( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::RefreshCycleDurationGOOGLE  displayTimingProperties;
    Result result = static_cast<Result>( d.vkGetRefreshCycleDurationGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), reinterpret_cast<VkRefreshCycleDurationGOOGLE *>( &displayTimingProperties ) ) );
    return createResultValue( result, displayTimingProperties, VULKAN_HPP_NAMESPACE_STRING "::Device::getRefreshCycleDurationGOOGLE" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getPastPresentationTimingGOOGLE( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, uint32_t * pPresentationTimingCount, VULKAN_HPP_NAMESPACE::PastPresentationTimingGOOGLE * pPresentationTimings, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPastPresentationTimingGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), pPresentationTimingCount, reinterpret_cast<VkPastPresentationTimingGOOGLE *>( pPresentationTimings ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PastPresentationTimingGOOGLEAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PastPresentationTimingGOOGLE, PastPresentationTimingGOOGLEAllocator>>::type Device::getPastPresentationTimingGOOGLE( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PastPresentationTimingGOOGLE, PastPresentationTimingGOOGLEAllocator> presentationTimings;
    uint32_t presentationTimingCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPastPresentationTimingGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), &presentationTimingCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && presentationTimingCount )
      {
        presentationTimings.resize( presentationTimingCount );
        result = static_cast<Result>( d.vkGetPastPresentationTimingGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), &presentationTimingCount, reinterpret_cast<VkPastPresentationTimingGOOGLE *>( presentationTimings.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( presentationTimingCount <= presentationTimings.size() );
      if ( presentationTimingCount < presentationTimings.size() )
      {
        presentationTimings.resize( presentationTimingCount );
      }
    }
    return createResultValue( result, presentationTimings, VULKAN_HPP_NAMESPACE_STRING"::Device::getPastPresentationTimingGOOGLE" );
  }

  template <typename PastPresentationTimingGOOGLEAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PastPresentationTimingGOOGLE>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PastPresentationTimingGOOGLE, PastPresentationTimingGOOGLEAllocator>>::type Device::getPastPresentationTimingGOOGLE( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, PastPresentationTimingGOOGLEAllocator & pastPresentationTimingGOOGLEAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PastPresentationTimingGOOGLE, PastPresentationTimingGOOGLEAllocator> presentationTimings( pastPresentationTimingGOOGLEAllocator );
    uint32_t presentationTimingCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPastPresentationTimingGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), &presentationTimingCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && presentationTimingCount )
      {
        presentationTimings.resize( presentationTimingCount );
        result = static_cast<Result>( d.vkGetPastPresentationTimingGOOGLE( m_device, static_cast<VkSwapchainKHR>( swapchain ), &presentationTimingCount, reinterpret_cast<VkPastPresentationTimingGOOGLE *>( presentationTimings.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( presentationTimingCount <= presentationTimings.size() );
      if ( presentationTimingCount < presentationTimings.size() )
      {
        presentationTimings.resize( presentationTimingCount );
      }
    }
    return createResultValue( result, presentationTimings, VULKAN_HPP_NAMESPACE_STRING"::Device::getPastPresentationTimingGOOGLE" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_discard_rectangles ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDiscardRectangleEXT( uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VULKAN_HPP_NAMESPACE::Rect2D * pDiscardRectangles, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDiscardRectangleEXT( m_commandBuffer, firstDiscardRectangle, discardRectangleCount, reinterpret_cast<const VkRect2D *>( pDiscardRectangles ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDiscardRectangleEXT( uint32_t firstDiscardRectangle, ArrayProxy<const VULKAN_HPP_NAMESPACE::Rect2D> const & discardRectangles, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetDiscardRectangleEXT( m_commandBuffer, firstDiscardRectangle, discardRectangles.size(), reinterpret_cast<const VkRect2D *>( discardRectangles.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_hdr_metadata ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::setHdrMetadataEXT( uint32_t swapchainCount, const VULKAN_HPP_NAMESPACE::SwapchainKHR * pSwapchains, const VULKAN_HPP_NAMESPACE::HdrMetadataEXT * pMetadata, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkSetHdrMetadataEXT( m_device, swapchainCount, reinterpret_cast<const VkSwapchainKHR *>( pSwapchains ), reinterpret_cast<const VkHdrMetadataEXT *>( pMetadata ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::setHdrMetadataEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::SwapchainKHR> const & swapchains, ArrayProxy<const VULKAN_HPP_NAMESPACE::HdrMetadataEXT> const & metadata, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( swapchains.size() == metadata.size() );
#else
    if ( swapchains.size() != metadata.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::Device::setHdrMetadataEXT: swapchains.size() != metadata.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkSetHdrMetadataEXT( m_device, swapchains.size(), reinterpret_cast<const VkSwapchainKHR *>( swapchains.data() ), reinterpret_cast<const VkHdrMetadataEXT *>( metadata.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_create_renderpass2 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createRenderPass2KHR( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo2 * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::RenderPass * pRenderPass, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateRenderPass2KHR( m_device, reinterpret_cast<const VkRenderPassCreateInfo2 *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkRenderPass *>( pRenderPass ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::RenderPass >::type Device::createRenderPass2KHR( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo2 & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::RenderPass  renderPass;
    Result result = static_cast<Result>( d.vkCreateRenderPass2KHR( m_device, reinterpret_cast<const VkRenderPassCreateInfo2 *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkRenderPass *>( &renderPass ) ) );
    return createResultValue( result, renderPass, VULKAN_HPP_NAMESPACE_STRING "::Device::createRenderPass2KHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::RenderPass, Dispatch>>::type Device::createRenderPass2KHRUnique( const VULKAN_HPP_NAMESPACE::RenderPassCreateInfo2 & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::RenderPass renderPass;
    Result result = static_cast<Result>( d.vkCreateRenderPass2KHR( m_device, reinterpret_cast<const VkRenderPassCreateInfo2 *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkRenderPass *>( &renderPass ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::RenderPass, Dispatch>( result, renderPass, VULKAN_HPP_NAMESPACE_STRING "::Device::createRenderPass2KHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderPass2KHR( const VULKAN_HPP_NAMESPACE::RenderPassBeginInfo * pRenderPassBegin, const VULKAN_HPP_NAMESPACE::SubpassBeginInfo * pSubpassBeginInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginRenderPass2KHR( m_commandBuffer, reinterpret_cast<const VkRenderPassBeginInfo *>( pRenderPassBegin ), reinterpret_cast<const VkSubpassBeginInfo *>( pSubpassBeginInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginRenderPass2KHR( const VULKAN_HPP_NAMESPACE::RenderPassBeginInfo & renderPassBegin, const VULKAN_HPP_NAMESPACE::SubpassBeginInfo & subpassBeginInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginRenderPass2KHR( m_commandBuffer, reinterpret_cast<const VkRenderPassBeginInfo *>( &renderPassBegin ), reinterpret_cast<const VkSubpassBeginInfo *>( &subpassBeginInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::nextSubpass2KHR( const VULKAN_HPP_NAMESPACE::SubpassBeginInfo * pSubpassBeginInfo, const VULKAN_HPP_NAMESPACE::SubpassEndInfo * pSubpassEndInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdNextSubpass2KHR( m_commandBuffer, reinterpret_cast<const VkSubpassBeginInfo *>( pSubpassBeginInfo ), reinterpret_cast<const VkSubpassEndInfo *>( pSubpassEndInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::nextSubpass2KHR( const VULKAN_HPP_NAMESPACE::SubpassBeginInfo & subpassBeginInfo, const VULKAN_HPP_NAMESPACE::SubpassEndInfo & subpassEndInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdNextSubpass2KHR( m_commandBuffer, reinterpret_cast<const VkSubpassBeginInfo *>( &subpassBeginInfo ), reinterpret_cast<const VkSubpassEndInfo *>( &subpassEndInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRenderPass2KHR( const VULKAN_HPP_NAMESPACE::SubpassEndInfo * pSubpassEndInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndRenderPass2KHR( m_commandBuffer, reinterpret_cast<const VkSubpassEndInfo *>( pSubpassEndInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endRenderPass2KHR( const VULKAN_HPP_NAMESPACE::SubpassEndInfo & subpassEndInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdEndRenderPass2KHR( m_commandBuffer, reinterpret_cast<const VkSubpassEndInfo *>( &subpassEndInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_shared_presentable_image ===


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSwapchainStatusKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSwapchainStatusKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSwapchainStatusKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkGetSwapchainStatusKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::getSwapchainStatusKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eSuboptimalKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_external_fence_capabilities ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getExternalFencePropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalFenceInfo * pExternalFenceInfo, VULKAN_HPP_NAMESPACE::ExternalFenceProperties * pExternalFenceProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceExternalFencePropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo *>( pExternalFenceInfo ), reinterpret_cast<VkExternalFenceProperties *>( pExternalFenceProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::ExternalFenceProperties  PhysicalDevice::getExternalFencePropertiesKHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceExternalFenceInfo & externalFenceInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ExternalFenceProperties  externalFenceProperties;
    d.vkGetPhysicalDeviceExternalFencePropertiesKHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo *>( &externalFenceInfo ), reinterpret_cast<VkExternalFenceProperties *>( &externalFenceProperties ) );
    return externalFenceProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_fence_win32 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::importFenceWin32HandleKHR( const VULKAN_HPP_NAMESPACE::ImportFenceWin32HandleInfoKHR * pImportFenceWin32HandleInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkImportFenceWin32HandleKHR( m_device, reinterpret_cast<const VkImportFenceWin32HandleInfoKHR *>( pImportFenceWin32HandleInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::importFenceWin32HandleKHR( const VULKAN_HPP_NAMESPACE::ImportFenceWin32HandleInfoKHR & importFenceWin32HandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkImportFenceWin32HandleKHR( m_device, reinterpret_cast<const VkImportFenceWin32HandleInfoKHR *>( &importFenceWin32HandleInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::importFenceWin32HandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getFenceWin32HandleKHR( const VULKAN_HPP_NAMESPACE::FenceGetWin32HandleInfoKHR * pGetWin32HandleInfo, HANDLE * pHandle, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetFenceWin32HandleKHR( m_device, reinterpret_cast<const VkFenceGetWin32HandleInfoKHR *>( pGetWin32HandleInfo ), pHandle ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<HANDLE >::type Device::getFenceWin32HandleKHR( const VULKAN_HPP_NAMESPACE::FenceGetWin32HandleInfoKHR & getWin32HandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    HANDLE  handle;
    Result result = static_cast<Result>( d.vkGetFenceWin32HandleKHR( m_device, reinterpret_cast<const VkFenceGetWin32HandleInfoKHR *>( &getWin32HandleInfo ), &handle ) );
    return createResultValue( result, handle, VULKAN_HPP_NAMESPACE_STRING "::Device::getFenceWin32HandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_fence_fd ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::importFenceFdKHR( const VULKAN_HPP_NAMESPACE::ImportFenceFdInfoKHR * pImportFenceFdInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkImportFenceFdKHR( m_device, reinterpret_cast<const VkImportFenceFdInfoKHR *>( pImportFenceFdInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::importFenceFdKHR( const VULKAN_HPP_NAMESPACE::ImportFenceFdInfoKHR & importFenceFdInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkImportFenceFdKHR( m_device, reinterpret_cast<const VkImportFenceFdInfoKHR *>( &importFenceFdInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::importFenceFdKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getFenceFdKHR( const VULKAN_HPP_NAMESPACE::FenceGetFdInfoKHR * pGetFdInfo, int * pFd, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetFenceFdKHR( m_device, reinterpret_cast<const VkFenceGetFdInfoKHR *>( pGetFdInfo ), pFd ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<int >::type Device::getFenceFdKHR( const VULKAN_HPP_NAMESPACE::FenceGetFdInfoKHR & getFdInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    int  fd;
    Result result = static_cast<Result>( d.vkGetFenceFdKHR( m_device, reinterpret_cast<const VkFenceGetFdInfoKHR *>( &getFdInfo ), &fd ) );
    return createResultValue( result, fd, VULKAN_HPP_NAMESPACE_STRING "::Device::getFenceFdKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_performance_query ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::enumerateQueueFamilyPerformanceQueryCountersKHR( uint32_t queueFamilyIndex, uint32_t * pCounterCount, VULKAN_HPP_NAMESPACE::PerformanceCounterKHR * pCounters, VULKAN_HPP_NAMESPACE::PerformanceCounterDescriptionKHR * pCounterDescriptions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR( m_physicalDevice, queueFamilyIndex, pCounterCount, reinterpret_cast<VkPerformanceCounterKHR *>( pCounters ), reinterpret_cast<VkPerformanceCounterDescriptionKHR *>( pCounterDescriptions ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PerformanceCounterKHRAllocator, typename PerformanceCounterDescriptionKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::pair<std::vector<PerformanceCounterKHR, PerformanceCounterKHRAllocator>, std::vector<PerformanceCounterDescriptionKHR, PerformanceCounterDescriptionKHRAllocator>>>::type PhysicalDevice::enumerateQueueFamilyPerformanceQueryCountersKHR( uint32_t queueFamilyIndex, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::pair<std::vector<PerformanceCounterKHR, PerformanceCounterKHRAllocator>, std::vector<PerformanceCounterDescriptionKHR, PerformanceCounterDescriptionKHRAllocator>> data;
    std::vector<PerformanceCounterKHR, PerformanceCounterKHRAllocator> & counters = data.first;
    std::vector<PerformanceCounterDescriptionKHR, PerformanceCounterDescriptionKHRAllocator> & counterDescriptions = data.second;
    uint32_t counterCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR( m_physicalDevice, queueFamilyIndex, &counterCount, nullptr, nullptr ) );
      if ( ( result == Result::eSuccess ) && counterCount )
      {
        counters.resize( counterCount );
        counterDescriptions.resize( counterCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR( m_physicalDevice, queueFamilyIndex, &counterCount, reinterpret_cast<VkPerformanceCounterKHR *>( counters.data() ), reinterpret_cast<VkPerformanceCounterDescriptionKHR *>( counterDescriptions.data() ) ) );
        VULKAN_HPP_ASSERT( counterCount <= counters.size() );
      }
    } while ( result == Result::eIncomplete );
    if ( ( result == Result::eSuccess ) && ( counterCount < counters.size() ) )
    {
      counters.resize( counterCount );
      counterDescriptions.resize( counterCount );
    }
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::enumerateQueueFamilyPerformanceQueryCountersKHR" );
  }

  template <typename PerformanceCounterKHRAllocator, typename PerformanceCounterDescriptionKHRAllocator, typename Dispatch, typename B1, typename B2, typename std::enable_if<std::is_same<typename B1::value_type, PerformanceCounterKHR>::value && std::is_same<typename B2::value_type, PerformanceCounterDescriptionKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::pair<std::vector<PerformanceCounterKHR, PerformanceCounterKHRAllocator>, std::vector<PerformanceCounterDescriptionKHR, PerformanceCounterDescriptionKHRAllocator>>>::type PhysicalDevice::enumerateQueueFamilyPerformanceQueryCountersKHR( uint32_t queueFamilyIndex, PerformanceCounterKHRAllocator & performanceCounterKHRAllocator, PerformanceCounterDescriptionKHRAllocator & performanceCounterDescriptionKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::pair<std::vector<PerformanceCounterKHR, PerformanceCounterKHRAllocator>, std::vector<PerformanceCounterDescriptionKHR, PerformanceCounterDescriptionKHRAllocator>> data( std::piecewise_construct, std::forward_as_tuple( performanceCounterKHRAllocator ), std::forward_as_tuple( performanceCounterDescriptionKHRAllocator ) );
    std::vector<PerformanceCounterKHR, PerformanceCounterKHRAllocator> & counters = data.first;
    std::vector<PerformanceCounterDescriptionKHR, PerformanceCounterDescriptionKHRAllocator> & counterDescriptions = data.second;
    uint32_t counterCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR( m_physicalDevice, queueFamilyIndex, &counterCount, nullptr, nullptr ) );
      if ( ( result == Result::eSuccess ) && counterCount )
      {
        counters.resize( counterCount );
        counterDescriptions.resize( counterCount );
        result = static_cast<Result>( d.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR( m_physicalDevice, queueFamilyIndex, &counterCount, reinterpret_cast<VkPerformanceCounterKHR *>( counters.data() ), reinterpret_cast<VkPerformanceCounterDescriptionKHR *>( counterDescriptions.data() ) ) );
        VULKAN_HPP_ASSERT( counterCount <= counters.size() );
      }
    } while ( result == Result::eIncomplete );
    if ( ( result == Result::eSuccess ) && ( counterCount < counters.size() ) )
    {
      counters.resize( counterCount );
      counterDescriptions.resize( counterCount );
    }
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::enumerateQueueFamilyPerformanceQueryCountersKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getQueueFamilyPerformanceQueryPassesKHR( const VULKAN_HPP_NAMESPACE::QueryPoolPerformanceCreateInfoKHR * pPerformanceQueryCreateInfo, uint32_t * pNumPasses, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR( m_physicalDevice, reinterpret_cast<const VkQueryPoolPerformanceCreateInfoKHR *>( pPerformanceQueryCreateInfo ), pNumPasses );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE uint32_t  PhysicalDevice::getQueueFamilyPerformanceQueryPassesKHR( const VULKAN_HPP_NAMESPACE::QueryPoolPerformanceCreateInfoKHR & performanceQueryCreateInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint32_t  numPasses;
    d.vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR( m_physicalDevice, reinterpret_cast<const VkQueryPoolPerformanceCreateInfoKHR *>( &performanceQueryCreateInfo ), &numPasses );
    return numPasses;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::acquireProfilingLockKHR( const VULKAN_HPP_NAMESPACE::AcquireProfilingLockInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireProfilingLockKHR( m_device, reinterpret_cast<const VkAcquireProfilingLockInfoKHR *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::acquireProfilingLockKHR( const VULKAN_HPP_NAMESPACE::AcquireProfilingLockInfoKHR & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkAcquireProfilingLockKHR( m_device, reinterpret_cast<const VkAcquireProfilingLockInfoKHR *>( &info ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::acquireProfilingLockKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::releaseProfilingLockKHR( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkReleaseProfilingLockKHR( m_device );
  }

  //=== VK_KHR_get_surface_capabilities2 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfaceCapabilities2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR * pSurfaceInfo, VULKAN_HPP_NAMESPACE::SurfaceCapabilities2KHR * pSurfaceCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilities2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( pSurfaceInfo ), reinterpret_cast<VkSurfaceCapabilities2KHR *>( pSurfaceCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceCapabilities2KHR >::type PhysicalDevice::getSurfaceCapabilities2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceCapabilities2KHR  surfaceCapabilities;
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilities2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), reinterpret_cast<VkSurfaceCapabilities2KHR *>( &surfaceCapabilities ) ) );
    return createResultValue( result, surfaceCapabilities, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getSurfaceCapabilities2KHR" );
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<StructureChain<X, Y, Z...>>::type PhysicalDevice::getSurfaceCapabilities2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::SurfaceCapabilities2KHR & surfaceCapabilities = structureChain.template get<VULKAN_HPP_NAMESPACE::SurfaceCapabilities2KHR>();
    Result result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceCapabilities2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), reinterpret_cast<VkSurfaceCapabilities2KHR *>( &surfaceCapabilities ) ) );
    return createResultValue( result, structureChain, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfaceCapabilities2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfaceFormats2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR * pSurfaceInfo, uint32_t * pSurfaceFormatCount, VULKAN_HPP_NAMESPACE::SurfaceFormat2KHR * pSurfaceFormats, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormats2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( pSurfaceInfo ), pSurfaceFormatCount, reinterpret_cast<VkSurfaceFormat2KHR *>( pSurfaceFormats ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SurfaceFormat2KHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<SurfaceFormat2KHR, SurfaceFormat2KHRAllocator>>::type PhysicalDevice::getSurfaceFormats2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SurfaceFormat2KHR, SurfaceFormat2KHRAllocator> surfaceFormats;
    uint32_t surfaceFormatCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormats2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &surfaceFormatCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && surfaceFormatCount )
      {
        surfaceFormats.resize( surfaceFormatCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormats2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &surfaceFormatCount, reinterpret_cast<VkSurfaceFormat2KHR *>( surfaceFormats.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( surfaceFormatCount <= surfaceFormats.size() );
      if ( surfaceFormatCount < surfaceFormats.size() )
      {
        surfaceFormats.resize( surfaceFormatCount );
      }
    }
    return createResultValue( result, surfaceFormats, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfaceFormats2KHR" );
  }

  template <typename SurfaceFormat2KHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SurfaceFormat2KHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<SurfaceFormat2KHR, SurfaceFormat2KHRAllocator>>::type PhysicalDevice::getSurfaceFormats2KHR( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, SurfaceFormat2KHRAllocator & surfaceFormat2KHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SurfaceFormat2KHR, SurfaceFormat2KHRAllocator> surfaceFormats( surfaceFormat2KHRAllocator );
    uint32_t surfaceFormatCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormats2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &surfaceFormatCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && surfaceFormatCount )
      {
        surfaceFormats.resize( surfaceFormatCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfaceFormats2KHR( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &surfaceFormatCount, reinterpret_cast<VkSurfaceFormat2KHR *>( surfaceFormats.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( surfaceFormatCount <= surfaceFormats.size() );
      if ( surfaceFormatCount < surfaceFormats.size() )
      {
        surfaceFormats.resize( surfaceFormatCount );
      }
    }
    return createResultValue( result, surfaceFormats, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfaceFormats2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_get_display_properties2 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayProperties2KHR( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::DisplayProperties2KHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceDisplayProperties2KHR( m_physicalDevice, pPropertyCount, reinterpret_cast<VkDisplayProperties2KHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayProperties2KHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayProperties2KHR, DisplayProperties2KHRAllocator>>::type PhysicalDevice::getDisplayProperties2KHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayProperties2KHR, DisplayProperties2KHRAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayProperties2KHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayProperties2KHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayProperties2KHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayProperties2KHR" );
  }

  template <typename DisplayProperties2KHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayProperties2KHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayProperties2KHR, DisplayProperties2KHRAllocator>>::type PhysicalDevice::getDisplayProperties2KHR( DisplayProperties2KHRAllocator & displayProperties2KHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayProperties2KHR, DisplayProperties2KHRAllocator> properties( displayProperties2KHRAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayProperties2KHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayProperties2KHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayProperties2KHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayProperties2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayPlaneProperties2KHR( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::DisplayPlaneProperties2KHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlaneProperties2KHR( m_physicalDevice, pPropertyCount, reinterpret_cast<VkDisplayPlaneProperties2KHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayPlaneProperties2KHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayPlaneProperties2KHR, DisplayPlaneProperties2KHRAllocator>>::type PhysicalDevice::getDisplayPlaneProperties2KHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayPlaneProperties2KHR, DisplayPlaneProperties2KHRAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlaneProperties2KHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlaneProperties2KHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayPlaneProperties2KHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPlaneProperties2KHR" );
  }

  template <typename DisplayPlaneProperties2KHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayPlaneProperties2KHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayPlaneProperties2KHR, DisplayPlaneProperties2KHRAllocator>>::type PhysicalDevice::getDisplayPlaneProperties2KHR( DisplayPlaneProperties2KHRAllocator & displayPlaneProperties2KHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayPlaneProperties2KHR, DisplayPlaneProperties2KHRAllocator> properties( displayPlaneProperties2KHRAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlaneProperties2KHR( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceDisplayPlaneProperties2KHR( m_physicalDevice, &propertyCount, reinterpret_cast<VkDisplayPlaneProperties2KHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayPlaneProperties2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayModeProperties2KHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::DisplayModeProperties2KHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDisplayModeProperties2KHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), pPropertyCount, reinterpret_cast<VkDisplayModeProperties2KHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DisplayModeProperties2KHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayModeProperties2KHR, DisplayModeProperties2KHRAllocator>>::type PhysicalDevice::getDisplayModeProperties2KHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayModeProperties2KHR, DisplayModeProperties2KHRAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetDisplayModeProperties2KHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetDisplayModeProperties2KHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, reinterpret_cast<VkDisplayModeProperties2KHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayModeProperties2KHR" );
  }

  template <typename DisplayModeProperties2KHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, DisplayModeProperties2KHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<DisplayModeProperties2KHR, DisplayModeProperties2KHRAllocator>>::type PhysicalDevice::getDisplayModeProperties2KHR( VULKAN_HPP_NAMESPACE::DisplayKHR display, DisplayModeProperties2KHRAllocator & displayModeProperties2KHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<DisplayModeProperties2KHR, DisplayModeProperties2KHRAllocator> properties( displayModeProperties2KHRAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetDisplayModeProperties2KHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetDisplayModeProperties2KHR( m_physicalDevice, static_cast<VkDisplayKHR>( display ), &propertyCount, reinterpret_cast<VkDisplayModeProperties2KHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getDisplayModeProperties2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDisplayPlaneCapabilities2KHR( const VULKAN_HPP_NAMESPACE::DisplayPlaneInfo2KHR * pDisplayPlaneInfo, VULKAN_HPP_NAMESPACE::DisplayPlaneCapabilities2KHR * pCapabilities, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDisplayPlaneCapabilities2KHR( m_physicalDevice, reinterpret_cast<const VkDisplayPlaneInfo2KHR *>( pDisplayPlaneInfo ), reinterpret_cast<VkDisplayPlaneCapabilities2KHR *>( pCapabilities ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DisplayPlaneCapabilities2KHR >::type PhysicalDevice::getDisplayPlaneCapabilities2KHR( const VULKAN_HPP_NAMESPACE::DisplayPlaneInfo2KHR & displayPlaneInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DisplayPlaneCapabilities2KHR  capabilities;
    Result result = static_cast<Result>( d.vkGetDisplayPlaneCapabilities2KHR( m_physicalDevice, reinterpret_cast<const VkDisplayPlaneInfo2KHR *>( &displayPlaneInfo ), reinterpret_cast<VkDisplayPlaneCapabilities2KHR *>( &capabilities ) ) );
    return createResultValue( result, capabilities, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getDisplayPlaneCapabilities2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_IOS_MVK )
  //=== VK_MVK_ios_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createIOSSurfaceMVK( const VULKAN_HPP_NAMESPACE::IOSSurfaceCreateInfoMVK * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateIOSSurfaceMVK( m_instance, reinterpret_cast<const VkIOSSurfaceCreateInfoMVK *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createIOSSurfaceMVK( const VULKAN_HPP_NAMESPACE::IOSSurfaceCreateInfoMVK & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateIOSSurfaceMVK( m_instance, reinterpret_cast<const VkIOSSurfaceCreateInfoMVK *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createIOSSurfaceMVK" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createIOSSurfaceMVKUnique( const VULKAN_HPP_NAMESPACE::IOSSurfaceCreateInfoMVK & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateIOSSurfaceMVK( m_instance, reinterpret_cast<const VkIOSSurfaceCreateInfoMVK *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createIOSSurfaceMVKUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_IOS_MVK*/

#if defined( VK_USE_PLATFORM_MACOS_MVK )
  //=== VK_MVK_macos_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createMacOSSurfaceMVK( const VULKAN_HPP_NAMESPACE::MacOSSurfaceCreateInfoMVK * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateMacOSSurfaceMVK( m_instance, reinterpret_cast<const VkMacOSSurfaceCreateInfoMVK *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createMacOSSurfaceMVK( const VULKAN_HPP_NAMESPACE::MacOSSurfaceCreateInfoMVK & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateMacOSSurfaceMVK( m_instance, reinterpret_cast<const VkMacOSSurfaceCreateInfoMVK *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createMacOSSurfaceMVK" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createMacOSSurfaceMVKUnique( const VULKAN_HPP_NAMESPACE::MacOSSurfaceCreateInfoMVK & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateMacOSSurfaceMVK( m_instance, reinterpret_cast<const VkMacOSSurfaceCreateInfoMVK *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createMacOSSurfaceMVKUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_MACOS_MVK*/

  //=== VK_EXT_debug_utils ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setDebugUtilsObjectNameEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsObjectNameInfoEXT * pNameInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetDebugUtilsObjectNameEXT( m_device, reinterpret_cast<const VkDebugUtilsObjectNameInfoEXT *>( pNameInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setDebugUtilsObjectNameEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsObjectNameInfoEXT & nameInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetDebugUtilsObjectNameEXT( m_device, reinterpret_cast<const VkDebugUtilsObjectNameInfoEXT *>( &nameInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setDebugUtilsObjectNameEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setDebugUtilsObjectTagEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsObjectTagInfoEXT * pTagInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetDebugUtilsObjectTagEXT( m_device, reinterpret_cast<const VkDebugUtilsObjectTagInfoEXT *>( pTagInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setDebugUtilsObjectTagEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsObjectTagInfoEXT & tagInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetDebugUtilsObjectTagEXT( m_device, reinterpret_cast<const VkDebugUtilsObjectTagInfoEXT *>( &tagInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setDebugUtilsObjectTagEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::beginDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT * pLabelInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkQueueBeginDebugUtilsLabelEXT( m_queue, reinterpret_cast<const VkDebugUtilsLabelEXT *>( pLabelInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::beginDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT & labelInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkQueueBeginDebugUtilsLabelEXT( m_queue, reinterpret_cast<const VkDebugUtilsLabelEXT *>( &labelInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::endDebugUtilsLabelEXT( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkQueueEndDebugUtilsLabelEXT( m_queue );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::insertDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT * pLabelInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkQueueInsertDebugUtilsLabelEXT( m_queue, reinterpret_cast<const VkDebugUtilsLabelEXT *>( pLabelInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::insertDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT & labelInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkQueueInsertDebugUtilsLabelEXT( m_queue, reinterpret_cast<const VkDebugUtilsLabelEXT *>( &labelInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT * pLabelInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBeginDebugUtilsLabelEXT( m_commandBuffer, reinterpret_cast<const VkDebugUtilsLabelEXT *>( pLabelInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::beginDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT & labelInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBeginDebugUtilsLabelEXT( m_commandBuffer, reinterpret_cast<const VkDebugUtilsLabelEXT *>( &labelInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::endDebugUtilsLabelEXT( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEndDebugUtilsLabelEXT( m_commandBuffer );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::insertDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT * pLabelInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdInsertDebugUtilsLabelEXT( m_commandBuffer, reinterpret_cast<const VkDebugUtilsLabelEXT *>( pLabelInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::insertDebugUtilsLabelEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsLabelEXT & labelInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdInsertDebugUtilsLabelEXT( m_commandBuffer, reinterpret_cast<const VkDebugUtilsLabelEXT *>( &labelInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createDebugUtilsMessengerEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT * pMessenger, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDebugUtilsMessengerEXT( m_instance, reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDebugUtilsMessengerEXT *>( pMessenger ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT >::type Instance::createDebugUtilsMessengerEXT( const VULKAN_HPP_NAMESPACE::DebugUtilsMessengerCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT  messenger;
    Result result = static_cast<Result>( d.vkCreateDebugUtilsMessengerEXT( m_instance, reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDebugUtilsMessengerEXT *>( &messenger ) ) );
    return createResultValue( result, messenger, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDebugUtilsMessengerEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT, Dispatch>>::type Instance::createDebugUtilsMessengerEXTUnique( const VULKAN_HPP_NAMESPACE::DebugUtilsMessengerCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT messenger;
    Result result = static_cast<Result>( d.vkCreateDebugUtilsMessengerEXT( m_instance, reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDebugUtilsMessengerEXT *>( &messenger ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT, Dispatch>( result, messenger, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDebugUtilsMessengerEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroyDebugUtilsMessengerEXT( VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT messenger, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDebugUtilsMessengerEXT( m_instance, static_cast<VkDebugUtilsMessengerEXT>( messenger ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroyDebugUtilsMessengerEXT( VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT messenger, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDebugUtilsMessengerEXT( m_instance, static_cast<VkDebugUtilsMessengerEXT>( messenger ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT messenger, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDebugUtilsMessengerEXT( m_instance, static_cast<VkDebugUtilsMessengerEXT>( messenger ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::destroy( VULKAN_HPP_NAMESPACE::DebugUtilsMessengerEXT messenger, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDebugUtilsMessengerEXT( m_instance, static_cast<VkDebugUtilsMessengerEXT>( messenger ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::submitDebugUtilsMessageEXT( VULKAN_HPP_NAMESPACE::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VULKAN_HPP_NAMESPACE::DebugUtilsMessageTypeFlagsEXT messageTypes, const VULKAN_HPP_NAMESPACE::DebugUtilsMessengerCallbackDataEXT * pCallbackData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkSubmitDebugUtilsMessageEXT( m_instance, static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>( messageSeverity ), static_cast<VkDebugUtilsMessageTypeFlagsEXT>( messageTypes ), reinterpret_cast<const VkDebugUtilsMessengerCallbackDataEXT *>( pCallbackData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Instance::submitDebugUtilsMessageEXT( VULKAN_HPP_NAMESPACE::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VULKAN_HPP_NAMESPACE::DebugUtilsMessageTypeFlagsEXT messageTypes, const VULKAN_HPP_NAMESPACE::DebugUtilsMessengerCallbackDataEXT & callbackData, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkSubmitDebugUtilsMessageEXT( m_instance, static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>( messageSeverity ), static_cast<VkDebugUtilsMessageTypeFlagsEXT>( messageTypes ), reinterpret_cast<const VkDebugUtilsMessengerCallbackDataEXT *>( &callbackData ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_ANDROID_external_memory_android_hardware_buffer ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getAndroidHardwareBufferPropertiesANDROID( const struct AHardwareBuffer * buffer, VULKAN_HPP_NAMESPACE::AndroidHardwareBufferPropertiesANDROID * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetAndroidHardwareBufferPropertiesANDROID( m_device, buffer, reinterpret_cast<VkAndroidHardwareBufferPropertiesANDROID *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::AndroidHardwareBufferPropertiesANDROID >::type Device::getAndroidHardwareBufferPropertiesANDROID( const struct AHardwareBuffer & buffer, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::AndroidHardwareBufferPropertiesANDROID  properties;
    Result result = static_cast<Result>( d.vkGetAndroidHardwareBufferPropertiesANDROID( m_device, &buffer, reinterpret_cast<VkAndroidHardwareBufferPropertiesANDROID *>( &properties ) ) );
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING "::Device::getAndroidHardwareBufferPropertiesANDROID" );
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<StructureChain<X, Y, Z...>>::type Device::getAndroidHardwareBufferPropertiesANDROID( const struct AHardwareBuffer & buffer, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::AndroidHardwareBufferPropertiesANDROID & properties = structureChain.template get<VULKAN_HPP_NAMESPACE::AndroidHardwareBufferPropertiesANDROID>();
    Result result = static_cast<Result>( d.vkGetAndroidHardwareBufferPropertiesANDROID( m_device, &buffer, reinterpret_cast<VkAndroidHardwareBufferPropertiesANDROID *>( &properties ) ) );
    return createResultValue( result, structureChain, VULKAN_HPP_NAMESPACE_STRING"::Device::getAndroidHardwareBufferPropertiesANDROID" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryAndroidHardwareBufferANDROID( const VULKAN_HPP_NAMESPACE::MemoryGetAndroidHardwareBufferInfoANDROID * pInfo, struct AHardwareBuffer ** pBuffer, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryAndroidHardwareBufferANDROID( m_device, reinterpret_cast<const VkMemoryGetAndroidHardwareBufferInfoANDROID *>( pInfo ), pBuffer ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<struct AHardwareBuffer *>::type Device::getMemoryAndroidHardwareBufferANDROID( const VULKAN_HPP_NAMESPACE::MemoryGetAndroidHardwareBufferInfoANDROID & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    struct AHardwareBuffer * buffer;
    Result result = static_cast<Result>( d.vkGetMemoryAndroidHardwareBufferANDROID( m_device, reinterpret_cast<const VkMemoryGetAndroidHardwareBufferInfoANDROID *>( &info ), &buffer ) );
    return createResultValue( result, buffer, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryAndroidHardwareBufferANDROID" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

  //=== VK_EXT_sample_locations ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setSampleLocationsEXT( const VULKAN_HPP_NAMESPACE::SampleLocationsInfoEXT * pSampleLocationsInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetSampleLocationsEXT( m_commandBuffer, reinterpret_cast<const VkSampleLocationsInfoEXT *>( pSampleLocationsInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setSampleLocationsEXT( const VULKAN_HPP_NAMESPACE::SampleLocationsInfoEXT & sampleLocationsInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetSampleLocationsEXT( m_commandBuffer, reinterpret_cast<const VkSampleLocationsInfoEXT *>( &sampleLocationsInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void PhysicalDevice::getMultisamplePropertiesEXT( VULKAN_HPP_NAMESPACE::SampleCountFlagBits samples, VULKAN_HPP_NAMESPACE::MultisamplePropertiesEXT * pMultisampleProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPhysicalDeviceMultisamplePropertiesEXT( m_physicalDevice, static_cast<VkSampleCountFlagBits>( samples ), reinterpret_cast<VkMultisamplePropertiesEXT *>( pMultisampleProperties ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MultisamplePropertiesEXT  PhysicalDevice::getMultisamplePropertiesEXT( VULKAN_HPP_NAMESPACE::SampleCountFlagBits samples, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MultisamplePropertiesEXT  multisampleProperties;
    d.vkGetPhysicalDeviceMultisamplePropertiesEXT( m_physicalDevice, static_cast<VkSampleCountFlagBits>( samples ), reinterpret_cast<VkMultisamplePropertiesEXT *>( &multisampleProperties ) );
    return multisampleProperties;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_get_memory_requirements2 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::ImageMemoryRequirementsInfo2 * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageMemoryRequirementsInfo2 *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getImageMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::ImageMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetImageMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getImageMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::ImageMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetImageMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getBufferMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::BufferMemoryRequirementsInfo2 * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetBufferMemoryRequirements2KHR( m_device, reinterpret_cast<const VkBufferMemoryRequirementsInfo2 *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getBufferMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::BufferMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetBufferMemoryRequirements2KHR( m_device, reinterpret_cast<const VkBufferMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getBufferMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::BufferMemoryRequirementsInfo2 & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetBufferMemoryRequirements2KHR( m_device, reinterpret_cast<const VkBufferMemoryRequirementsInfo2 *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageSparseMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::ImageSparseMemoryRequirementsInfo2 * pInfo, uint32_t * pSparseMemoryRequirementCount, VULKAN_HPP_NAMESPACE::SparseImageMemoryRequirements2 * pSparseMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetImageSparseMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( pInfo ), pSparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( pSparseMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::ImageSparseMemoryRequirementsInfo2 & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements;
    uint32_t sparseMemoryRequirementCount;
    d.vkGetImageSparseMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetImageSparseMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }

  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageMemoryRequirements2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirements2KHR( const VULKAN_HPP_NAMESPACE::ImageSparseMemoryRequirementsInfo2 & info, SparseImageMemoryRequirements2Allocator & sparseImageMemoryRequirements2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements( sparseImageMemoryRequirements2Allocator );
    uint32_t sparseMemoryRequirementCount;
    d.vkGetImageSparseMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetImageSparseMemoryRequirements2KHR( m_device, reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2 *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_acceleration_structure ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createAccelerationStructureKHR( const VULKAN_HPP_NAMESPACE::AccelerationStructureCreateInfoKHR * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::AccelerationStructureKHR * pAccelerationStructure, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateAccelerationStructureKHR( m_device, reinterpret_cast<const VkAccelerationStructureCreateInfoKHR *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkAccelerationStructureKHR *>( pAccelerationStructure ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::AccelerationStructureKHR >::type Device::createAccelerationStructureKHR( const VULKAN_HPP_NAMESPACE::AccelerationStructureCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::AccelerationStructureKHR  accelerationStructure;
    Result result = static_cast<Result>( d.vkCreateAccelerationStructureKHR( m_device, reinterpret_cast<const VkAccelerationStructureCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkAccelerationStructureKHR *>( &accelerationStructure ) ) );
    return createResultValue( result, accelerationStructure, VULKAN_HPP_NAMESPACE_STRING "::Device::createAccelerationStructureKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::AccelerationStructureKHR, Dispatch>>::type Device::createAccelerationStructureKHRUnique( const VULKAN_HPP_NAMESPACE::AccelerationStructureCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::AccelerationStructureKHR accelerationStructure;
    Result result = static_cast<Result>( d.vkCreateAccelerationStructureKHR( m_device, reinterpret_cast<const VkAccelerationStructureCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkAccelerationStructureKHR *>( &accelerationStructure ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::AccelerationStructureKHR, Dispatch>( result, accelerationStructure, VULKAN_HPP_NAMESPACE_STRING "::Device::createAccelerationStructureKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyAccelerationStructureKHR( VULKAN_HPP_NAMESPACE::AccelerationStructureKHR accelerationStructure, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyAccelerationStructureKHR( m_device, static_cast<VkAccelerationStructureKHR>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyAccelerationStructureKHR( VULKAN_HPP_NAMESPACE::AccelerationStructureKHR accelerationStructure, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyAccelerationStructureKHR( m_device, static_cast<VkAccelerationStructureKHR>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::AccelerationStructureKHR accelerationStructure, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyAccelerationStructureKHR( m_device, static_cast<VkAccelerationStructureKHR>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::AccelerationStructureKHR accelerationStructure, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyAccelerationStructureKHR( m_device, static_cast<VkAccelerationStructureKHR>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::buildAccelerationStructuresKHR( uint32_t infoCount, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR * pInfos, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildRangeInfoKHR * const * ppBuildRangeInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBuildAccelerationStructuresKHR( m_commandBuffer, infoCount, reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( pInfos ), reinterpret_cast<const VkAccelerationStructureBuildRangeInfoKHR * const *>( ppBuildRangeInfos ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::buildAccelerationStructuresKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR> const & infos, ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildRangeInfoKHR * const> const & pBuildRangeInfos, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( infos.size() == pBuildRangeInfos.size() );
#else
    if ( infos.size() != pBuildRangeInfos.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::buildAccelerationStructuresKHR: infos.size() != pBuildRangeInfos.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBuildAccelerationStructuresKHR( m_commandBuffer, infos.size(), reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( infos.data() ), reinterpret_cast<const VkAccelerationStructureBuildRangeInfoKHR * const *>( pBuildRangeInfos.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::buildAccelerationStructuresIndirectKHR( uint32_t infoCount, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR * pInfos, const VULKAN_HPP_NAMESPACE::DeviceAddress * pIndirectDeviceAddresses, const uint32_t * pIndirectStrides, const uint32_t * const * ppMaxPrimitiveCounts, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBuildAccelerationStructuresIndirectKHR( m_commandBuffer, infoCount, reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( pInfos ), reinterpret_cast<const VkDeviceAddress *>( pIndirectDeviceAddresses ), pIndirectStrides, ppMaxPrimitiveCounts );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::buildAccelerationStructuresIndirectKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR> const & infos, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceAddress> const & indirectDeviceAddresses, ArrayProxy<const uint32_t> const & indirectStrides, ArrayProxy<const uint32_t * const> const & pMaxPrimitiveCounts, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( infos.size() == indirectDeviceAddresses.size() );
    VULKAN_HPP_ASSERT( infos.size() == indirectStrides.size() );
    VULKAN_HPP_ASSERT( infos.size() == pMaxPrimitiveCounts.size() );
#else
    if ( infos.size() != indirectDeviceAddresses.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::buildAccelerationStructuresIndirectKHR: infos.size() != indirectDeviceAddresses.size()" );
  }
    if ( infos.size() != indirectStrides.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::buildAccelerationStructuresIndirectKHR: infos.size() != indirectStrides.size()" );
  }
    if ( infos.size() != pMaxPrimitiveCounts.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::buildAccelerationStructuresIndirectKHR: infos.size() != pMaxPrimitiveCounts.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBuildAccelerationStructuresIndirectKHR( m_commandBuffer, infos.size(), reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( infos.data() ), reinterpret_cast<const VkDeviceAddress *>( indirectDeviceAddresses.data() ), indirectStrides.data(), pMaxPrimitiveCounts.data() );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::buildAccelerationStructuresKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, uint32_t infoCount, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR * pInfos, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildRangeInfoKHR * const * ppBuildRangeInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBuildAccelerationStructuresKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), infoCount, reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( pInfos ), reinterpret_cast<const VkAccelerationStructureBuildRangeInfoKHR * const *>( ppBuildRangeInfos ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::buildAccelerationStructuresKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR> const & infos, ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildRangeInfoKHR * const> const & pBuildRangeInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( infos.size() == pBuildRangeInfos.size() );
#else
    if ( infos.size() != pBuildRangeInfos.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::Device::buildAccelerationStructuresKHR: infos.size() != pBuildRangeInfos.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    Result result = static_cast<Result>( d.vkBuildAccelerationStructuresKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), infos.size(), reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( infos.data() ), reinterpret_cast<const VkAccelerationStructureBuildRangeInfoKHR * const *>( pBuildRangeInfos.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::buildAccelerationStructuresKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::copyAccelerationStructureKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCopyAccelerationStructureKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), reinterpret_cast<const VkCopyAccelerationStructureInfoKHR *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::copyAccelerationStructureKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureInfoKHR & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCopyAccelerationStructureKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), reinterpret_cast<const VkCopyAccelerationStructureInfoKHR *>( &info ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::copyAccelerationStructureKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::copyAccelerationStructureToMemoryKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureToMemoryInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCopyAccelerationStructureToMemoryKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::copyAccelerationStructureToMemoryKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureToMemoryInfoKHR & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCopyAccelerationStructureToMemoryKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR *>( &info ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::copyAccelerationStructureToMemoryKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::copyMemoryToAccelerationStructureKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, const VULKAN_HPP_NAMESPACE::CopyMemoryToAccelerationStructureInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCopyMemoryToAccelerationStructureKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::copyMemoryToAccelerationStructureKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, const VULKAN_HPP_NAMESPACE::CopyMemoryToAccelerationStructureInfoKHR & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCopyMemoryToAccelerationStructureKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR *>( &info ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::copyMemoryToAccelerationStructureKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::writeAccelerationStructuresPropertiesKHR( uint32_t accelerationStructureCount, const VULKAN_HPP_NAMESPACE::AccelerationStructureKHR * pAccelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, size_t dataSize, void * pData, size_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkWriteAccelerationStructuresPropertiesKHR( m_device, accelerationStructureCount, reinterpret_cast<const VkAccelerationStructureKHR *>( pAccelerationStructures ), static_cast<VkQueryType>( queryType ), dataSize, pData, stride ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<DataType,Allocator>>::type Device::writeAccelerationStructuresPropertiesKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureKHR> const & accelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, size_t dataSize, size_t stride, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_ASSERT( dataSize % sizeof( DataType ) == 0 );
    std::vector<DataType,Allocator> data( dataSize / sizeof( DataType ) );
    Result result = static_cast<Result>( d.vkWriteAccelerationStructuresPropertiesKHR( m_device, accelerationStructures.size(), reinterpret_cast<const VkAccelerationStructureKHR *>( accelerationStructures.data() ), static_cast<VkQueryType>( queryType ), data.size() * sizeof( DataType ), reinterpret_cast<void *>( data.data() ), stride ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::writeAccelerationStructuresPropertiesKHR" );
  }

  template <typename DataType, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<DataType>::type Device::writeAccelerationStructuresPropertyKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureKHR> const & accelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, size_t stride, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    DataType data;
    Result result = static_cast<Result>( d.vkWriteAccelerationStructuresPropertiesKHR( m_device, accelerationStructures.size(), reinterpret_cast<const VkAccelerationStructureKHR *>( accelerationStructures.data() ), static_cast<VkQueryType>( queryType ), sizeof( DataType ), reinterpret_cast<void *>( &data ), stride ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::writeAccelerationStructuresPropertyKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyAccelerationStructureKHR( const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyAccelerationStructureKHR( m_commandBuffer, reinterpret_cast<const VkCopyAccelerationStructureInfoKHR *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyAccelerationStructureKHR( const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureInfoKHR & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyAccelerationStructureKHR( m_commandBuffer, reinterpret_cast<const VkCopyAccelerationStructureInfoKHR *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyAccelerationStructureToMemoryKHR( const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureToMemoryInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyAccelerationStructureToMemoryKHR( m_commandBuffer, reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyAccelerationStructureToMemoryKHR( const VULKAN_HPP_NAMESPACE::CopyAccelerationStructureToMemoryInfoKHR & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyAccelerationStructureToMemoryKHR( m_commandBuffer, reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyMemoryToAccelerationStructureKHR( const VULKAN_HPP_NAMESPACE::CopyMemoryToAccelerationStructureInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyMemoryToAccelerationStructureKHR( m_commandBuffer, reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyMemoryToAccelerationStructureKHR( const VULKAN_HPP_NAMESPACE::CopyMemoryToAccelerationStructureInfoKHR & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyMemoryToAccelerationStructureKHR( m_commandBuffer, reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getAccelerationStructureAddressKHR( const VULKAN_HPP_NAMESPACE::AccelerationStructureDeviceAddressInfoKHR * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<DeviceAddress>( d.vkGetAccelerationStructureDeviceAddressKHR( m_device, reinterpret_cast<const VkAccelerationStructureDeviceAddressInfoKHR *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getAccelerationStructureAddressKHR( const VULKAN_HPP_NAMESPACE::AccelerationStructureDeviceAddressInfoKHR & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetAccelerationStructureDeviceAddressKHR( m_device, reinterpret_cast<const VkAccelerationStructureDeviceAddressInfoKHR *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeAccelerationStructuresPropertiesKHR( uint32_t accelerationStructureCount, const VULKAN_HPP_NAMESPACE::AccelerationStructureKHR * pAccelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteAccelerationStructuresPropertiesKHR( m_commandBuffer, accelerationStructureCount, reinterpret_cast<const VkAccelerationStructureKHR *>( pAccelerationStructures ), static_cast<VkQueryType>( queryType ), static_cast<VkQueryPool>( queryPool ), firstQuery );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeAccelerationStructuresPropertiesKHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureKHR> const & accelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdWriteAccelerationStructuresPropertiesKHR( m_commandBuffer, accelerationStructures.size(), reinterpret_cast<const VkAccelerationStructureKHR *>( accelerationStructures.data() ), static_cast<VkQueryType>( queryType ), static_cast<VkQueryPool>( queryPool ), firstQuery );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getAccelerationStructureCompatibilityKHR( const VULKAN_HPP_NAMESPACE::AccelerationStructureVersionInfoKHR * pVersionInfo, VULKAN_HPP_NAMESPACE::AccelerationStructureCompatibilityKHR * pCompatibility, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceAccelerationStructureCompatibilityKHR( m_device, reinterpret_cast<const VkAccelerationStructureVersionInfoKHR *>( pVersionInfo ), reinterpret_cast<VkAccelerationStructureCompatibilityKHR *>( pCompatibility ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::AccelerationStructureCompatibilityKHR  Device::getAccelerationStructureCompatibilityKHR( const VULKAN_HPP_NAMESPACE::AccelerationStructureVersionInfoKHR & versionInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::AccelerationStructureCompatibilityKHR  compatibility;
    d.vkGetDeviceAccelerationStructureCompatibilityKHR( m_device, reinterpret_cast<const VkAccelerationStructureVersionInfoKHR *>( &versionInfo ), reinterpret_cast<VkAccelerationStructureCompatibilityKHR *>( &compatibility ) );
    return compatibility;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getAccelerationStructureBuildSizesKHR( VULKAN_HPP_NAMESPACE::AccelerationStructureBuildTypeKHR buildType, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR * pBuildInfo, const uint32_t * pMaxPrimitiveCounts, VULKAN_HPP_NAMESPACE::AccelerationStructureBuildSizesInfoKHR * pSizeInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetAccelerationStructureBuildSizesKHR( m_device, static_cast<VkAccelerationStructureBuildTypeKHR>( buildType ), reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( pBuildInfo ), pMaxPrimitiveCounts, reinterpret_cast<VkAccelerationStructureBuildSizesInfoKHR *>( pSizeInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::AccelerationStructureBuildSizesInfoKHR  Device::getAccelerationStructureBuildSizesKHR( VULKAN_HPP_NAMESPACE::AccelerationStructureBuildTypeKHR buildType, const VULKAN_HPP_NAMESPACE::AccelerationStructureBuildGeometryInfoKHR & buildInfo, ArrayProxy<const uint32_t> const & maxPrimitiveCounts, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( maxPrimitiveCounts.size() == buildInfo.geometryCount );
#else
    if ( maxPrimitiveCounts.size() != buildInfo.geometryCount )
    {
      throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::Device::getAccelerationStructureBuildSizesKHR: maxPrimitiveCounts.size() != buildInfo.geometryCount" );
    }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    VULKAN_HPP_NAMESPACE::AccelerationStructureBuildSizesInfoKHR  sizeInfo;
    d.vkGetAccelerationStructureBuildSizesKHR( m_device, static_cast<VkAccelerationStructureBuildTypeKHR>( buildType ), reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR *>( &buildInfo ), maxPrimitiveCounts.data(), reinterpret_cast<VkAccelerationStructureBuildSizesInfoKHR *>( &sizeInfo ) );
    return sizeInfo;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_sampler_ycbcr_conversion ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createSamplerYcbcrConversionKHR( const VULKAN_HPP_NAMESPACE::SamplerYcbcrConversionCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion * pYcbcrConversion, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateSamplerYcbcrConversionKHR( m_device, reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSamplerYcbcrConversion *>( pYcbcrConversion ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion >::type Device::createSamplerYcbcrConversionKHR( const VULKAN_HPP_NAMESPACE::SamplerYcbcrConversionCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion  ycbcrConversion;
    Result result = static_cast<Result>( d.vkCreateSamplerYcbcrConversionKHR( m_device, reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSamplerYcbcrConversion *>( &ycbcrConversion ) ) );
    return createResultValue( result, ycbcrConversion, VULKAN_HPP_NAMESPACE_STRING "::Device::createSamplerYcbcrConversionKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion, Dispatch>>::type Device::createSamplerYcbcrConversionKHRUnique( const VULKAN_HPP_NAMESPACE::SamplerYcbcrConversionCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion;
    Result result = static_cast<Result>( d.vkCreateSamplerYcbcrConversionKHR( m_device, reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSamplerYcbcrConversion *>( &ycbcrConversion ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion, Dispatch>( result, ycbcrConversion, VULKAN_HPP_NAMESPACE_STRING "::Device::createSamplerYcbcrConversionKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySamplerYcbcrConversionKHR( VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroySamplerYcbcrConversionKHR( m_device, static_cast<VkSamplerYcbcrConversion>( ycbcrConversion ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroySamplerYcbcrConversionKHR( VULKAN_HPP_NAMESPACE::SamplerYcbcrConversion ycbcrConversion, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroySamplerYcbcrConversionKHR( m_device, static_cast<VkSamplerYcbcrConversion>( ycbcrConversion ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_bind_memory2 ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindBufferMemory2KHR( uint32_t bindInfoCount, const VULKAN_HPP_NAMESPACE::BindBufferMemoryInfo * pBindInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindBufferMemory2KHR( m_device, bindInfoCount, reinterpret_cast<const VkBindBufferMemoryInfo *>( pBindInfos ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindBufferMemory2KHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::BindBufferMemoryInfo> const & bindInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindBufferMemory2KHR( m_device, bindInfos.size(), reinterpret_cast<const VkBindBufferMemoryInfo *>( bindInfos.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindBufferMemory2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindImageMemory2KHR( uint32_t bindInfoCount, const VULKAN_HPP_NAMESPACE::BindImageMemoryInfo * pBindInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindImageMemory2KHR( m_device, bindInfoCount, reinterpret_cast<const VkBindImageMemoryInfo *>( pBindInfos ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindImageMemory2KHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::BindImageMemoryInfo> const & bindInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindImageMemory2KHR( m_device, bindInfos.size(), reinterpret_cast<const VkBindImageMemoryInfo *>( bindInfos.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindImageMemory2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_image_drm_format_modifier ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getImageDrmFormatModifierPropertiesEXT( VULKAN_HPP_NAMESPACE::Image image, VULKAN_HPP_NAMESPACE::ImageDrmFormatModifierPropertiesEXT * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetImageDrmFormatModifierPropertiesEXT( m_device, static_cast<VkImage>( image ), reinterpret_cast<VkImageDrmFormatModifierPropertiesEXT *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ImageDrmFormatModifierPropertiesEXT >::type Device::getImageDrmFormatModifierPropertiesEXT( VULKAN_HPP_NAMESPACE::Image image, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ImageDrmFormatModifierPropertiesEXT  properties;
    Result result = static_cast<Result>( d.vkGetImageDrmFormatModifierPropertiesEXT( m_device, static_cast<VkImage>( image ), reinterpret_cast<VkImageDrmFormatModifierPropertiesEXT *>( &properties ) ) );
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING "::Device::getImageDrmFormatModifierPropertiesEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_validation_cache ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createValidationCacheEXT( const VULKAN_HPP_NAMESPACE::ValidationCacheCreateInfoEXT * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::ValidationCacheEXT * pValidationCache, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateValidationCacheEXT( m_device, reinterpret_cast<const VkValidationCacheCreateInfoEXT *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkValidationCacheEXT *>( pValidationCache ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::ValidationCacheEXT >::type Device::createValidationCacheEXT( const VULKAN_HPP_NAMESPACE::ValidationCacheCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::ValidationCacheEXT  validationCache;
    Result result = static_cast<Result>( d.vkCreateValidationCacheEXT( m_device, reinterpret_cast<const VkValidationCacheCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkValidationCacheEXT *>( &validationCache ) ) );
    return createResultValue( result, validationCache, VULKAN_HPP_NAMESPACE_STRING "::Device::createValidationCacheEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::ValidationCacheEXT, Dispatch>>::type Device::createValidationCacheEXTUnique( const VULKAN_HPP_NAMESPACE::ValidationCacheCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache;
    Result result = static_cast<Result>( d.vkCreateValidationCacheEXT( m_device, reinterpret_cast<const VkValidationCacheCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkValidationCacheEXT *>( &validationCache ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::ValidationCacheEXT, Dispatch>( result, validationCache, VULKAN_HPP_NAMESPACE_STRING "::Device::createValidationCacheEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyValidationCacheEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyValidationCacheEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyValidationCacheEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyValidationCacheEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyValidationCacheEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyValidationCacheEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::mergeValidationCachesEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT dstCache, uint32_t srcCacheCount, const VULKAN_HPP_NAMESPACE::ValidationCacheEXT * pSrcCaches, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkMergeValidationCachesEXT( m_device, static_cast<VkValidationCacheEXT>( dstCache ), srcCacheCount, reinterpret_cast<const VkValidationCacheEXT *>( pSrcCaches ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::mergeValidationCachesEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT dstCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::ValidationCacheEXT> const & srcCaches, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkMergeValidationCachesEXT( m_device, static_cast<VkValidationCacheEXT>( dstCache ), srcCaches.size(), reinterpret_cast<const VkValidationCacheEXT *>( srcCaches.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::mergeValidationCachesEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getValidationCacheDataEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, size_t * pDataSize, void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetValidationCacheDataEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), pDataSize, pData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Uint8_tAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<uint8_t, Uint8_tAllocator>>::type Device::getValidationCacheDataEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<uint8_t, Uint8_tAllocator> data;
    size_t dataSize;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetValidationCacheDataEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), &dataSize, nullptr ) );
      if ( ( result == Result::eSuccess ) && dataSize )
      {
        data.resize( dataSize );
        result = static_cast<Result>( d.vkGetValidationCacheDataEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), &dataSize, reinterpret_cast<void *>( data.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( dataSize <= data.size() );
      if ( dataSize < data.size() )
      {
        data.resize( dataSize );
      }
    }
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING"::Device::getValidationCacheDataEXT" );
  }

  template <typename Uint8_tAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, uint8_t>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<uint8_t, Uint8_tAllocator>>::type Device::getValidationCacheDataEXT( VULKAN_HPP_NAMESPACE::ValidationCacheEXT validationCache, Uint8_tAllocator & uint8_tAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<uint8_t, Uint8_tAllocator> data( uint8_tAllocator );
    size_t dataSize;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetValidationCacheDataEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), &dataSize, nullptr ) );
      if ( ( result == Result::eSuccess ) && dataSize )
      {
        data.resize( dataSize );
        result = static_cast<Result>( d.vkGetValidationCacheDataEXT( m_device, static_cast<VkValidationCacheEXT>( validationCache ), &dataSize, reinterpret_cast<void *>( data.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( dataSize <= data.size() );
      if ( dataSize < data.size() )
      {
        data.resize( dataSize );
      }
    }
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING"::Device::getValidationCacheDataEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_shading_rate_image ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindShadingRateImageNV( VULKAN_HPP_NAMESPACE::ImageView imageView, VULKAN_HPP_NAMESPACE::ImageLayout imageLayout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindShadingRateImageNV( m_commandBuffer, static_cast<VkImageView>( imageView ), static_cast<VkImageLayout>( imageLayout ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportShadingRatePaletteNV( uint32_t firstViewport, uint32_t viewportCount, const VULKAN_HPP_NAMESPACE::ShadingRatePaletteNV * pShadingRatePalettes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetViewportShadingRatePaletteNV( m_commandBuffer, firstViewport, viewportCount, reinterpret_cast<const VkShadingRatePaletteNV *>( pShadingRatePalettes ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportShadingRatePaletteNV( uint32_t firstViewport, ArrayProxy<const VULKAN_HPP_NAMESPACE::ShadingRatePaletteNV> const & shadingRatePalettes, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetViewportShadingRatePaletteNV( m_commandBuffer, firstViewport, shadingRatePalettes.size(), reinterpret_cast<const VkShadingRatePaletteNV *>( shadingRatePalettes.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setCoarseSampleOrderNV( VULKAN_HPP_NAMESPACE::CoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VULKAN_HPP_NAMESPACE::CoarseSampleOrderCustomNV * pCustomSampleOrders, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetCoarseSampleOrderNV( m_commandBuffer, static_cast<VkCoarseSampleOrderTypeNV>( sampleOrderType ), customSampleOrderCount, reinterpret_cast<const VkCoarseSampleOrderCustomNV *>( pCustomSampleOrders ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setCoarseSampleOrderNV( VULKAN_HPP_NAMESPACE::CoarseSampleOrderTypeNV sampleOrderType, ArrayProxy<const VULKAN_HPP_NAMESPACE::CoarseSampleOrderCustomNV> const & customSampleOrders, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetCoarseSampleOrderNV( m_commandBuffer, static_cast<VkCoarseSampleOrderTypeNV>( sampleOrderType ), customSampleOrders.size(), reinterpret_cast<const VkCoarseSampleOrderCustomNV *>( customSampleOrders.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_ray_tracing ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createAccelerationStructureNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureCreateInfoNV * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::AccelerationStructureNV * pAccelerationStructure, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateAccelerationStructureNV( m_device, reinterpret_cast<const VkAccelerationStructureCreateInfoNV *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkAccelerationStructureNV *>( pAccelerationStructure ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::AccelerationStructureNV >::type Device::createAccelerationStructureNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureCreateInfoNV & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::AccelerationStructureNV  accelerationStructure;
    Result result = static_cast<Result>( d.vkCreateAccelerationStructureNV( m_device, reinterpret_cast<const VkAccelerationStructureCreateInfoNV *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkAccelerationStructureNV *>( &accelerationStructure ) ) );
    return createResultValue( result, accelerationStructure, VULKAN_HPP_NAMESPACE_STRING "::Device::createAccelerationStructureNV" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::AccelerationStructureNV, Dispatch>>::type Device::createAccelerationStructureNVUnique( const VULKAN_HPP_NAMESPACE::AccelerationStructureCreateInfoNV & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure;
    Result result = static_cast<Result>( d.vkCreateAccelerationStructureNV( m_device, reinterpret_cast<const VkAccelerationStructureCreateInfoNV *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkAccelerationStructureNV *>( &accelerationStructure ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::AccelerationStructureNV, Dispatch>( result, accelerationStructure, VULKAN_HPP_NAMESPACE_STRING "::Device::createAccelerationStructureNVUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyAccelerationStructureNV( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyAccelerationStructureNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyAccelerationStructureNV( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyAccelerationStructureNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyAccelerationStructureNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyAccelerationStructureNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getAccelerationStructureMemoryRequirementsNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureMemoryRequirementsInfoNV * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2KHR * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetAccelerationStructureMemoryRequirementsNV( m_device, reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoNV *>( pInfo ), reinterpret_cast<VkMemoryRequirements2KHR *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2KHR  Device::getAccelerationStructureMemoryRequirementsNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureMemoryRequirementsInfoNV & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2KHR  memoryRequirements;
    d.vkGetAccelerationStructureMemoryRequirementsNV( m_device, reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoNV *>( &info ), reinterpret_cast<VkMemoryRequirements2KHR *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getAccelerationStructureMemoryRequirementsNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureMemoryRequirementsInfoNV & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2KHR & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2KHR>();
    d.vkGetAccelerationStructureMemoryRequirementsNV( m_device, reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoNV *>( &info ), reinterpret_cast<VkMemoryRequirements2KHR *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::bindAccelerationStructureMemoryNV( uint32_t bindInfoCount, const VULKAN_HPP_NAMESPACE::BindAccelerationStructureMemoryInfoNV * pBindInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkBindAccelerationStructureMemoryNV( m_device, bindInfoCount, reinterpret_cast<const VkBindAccelerationStructureMemoryInfoNV *>( pBindInfos ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::bindAccelerationStructureMemoryNV( ArrayProxy<const VULKAN_HPP_NAMESPACE::BindAccelerationStructureMemoryInfoNV> const & bindInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkBindAccelerationStructureMemoryNV( m_device, bindInfos.size(), reinterpret_cast<const VkBindAccelerationStructureMemoryInfoNV *>( bindInfos.data() ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::bindAccelerationStructureMemoryNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::buildAccelerationStructureNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureInfoNV * pInfo, VULKAN_HPP_NAMESPACE::Buffer instanceData, VULKAN_HPP_NAMESPACE::DeviceSize instanceOffset, VULKAN_HPP_NAMESPACE::Bool32 update, VULKAN_HPP_NAMESPACE::AccelerationStructureNV dst, VULKAN_HPP_NAMESPACE::AccelerationStructureNV src, VULKAN_HPP_NAMESPACE::Buffer scratch, VULKAN_HPP_NAMESPACE::DeviceSize scratchOffset, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBuildAccelerationStructureNV( m_commandBuffer, reinterpret_cast<const VkAccelerationStructureInfoNV *>( pInfo ), static_cast<VkBuffer>( instanceData ), static_cast<VkDeviceSize>( instanceOffset ), static_cast<VkBool32>( update ), static_cast<VkAccelerationStructureNV>( dst ), static_cast<VkAccelerationStructureNV>( src ), static_cast<VkBuffer>( scratch ), static_cast<VkDeviceSize>( scratchOffset ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::buildAccelerationStructureNV( const VULKAN_HPP_NAMESPACE::AccelerationStructureInfoNV & info, VULKAN_HPP_NAMESPACE::Buffer instanceData, VULKAN_HPP_NAMESPACE::DeviceSize instanceOffset, VULKAN_HPP_NAMESPACE::Bool32 update, VULKAN_HPP_NAMESPACE::AccelerationStructureNV dst, VULKAN_HPP_NAMESPACE::AccelerationStructureNV src, VULKAN_HPP_NAMESPACE::Buffer scratch, VULKAN_HPP_NAMESPACE::DeviceSize scratchOffset, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBuildAccelerationStructureNV( m_commandBuffer, reinterpret_cast<const VkAccelerationStructureInfoNV *>( &info ), static_cast<VkBuffer>( instanceData ), static_cast<VkDeviceSize>( instanceOffset ), static_cast<VkBool32>( update ), static_cast<VkAccelerationStructureNV>( dst ), static_cast<VkAccelerationStructureNV>( src ), static_cast<VkBuffer>( scratch ), static_cast<VkDeviceSize>( scratchOffset ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyAccelerationStructureNV( VULKAN_HPP_NAMESPACE::AccelerationStructureNV dst, VULKAN_HPP_NAMESPACE::AccelerationStructureNV src, VULKAN_HPP_NAMESPACE::CopyAccelerationStructureModeKHR mode, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyAccelerationStructureNV( m_commandBuffer, static_cast<VkAccelerationStructureNV>( dst ), static_cast<VkAccelerationStructureNV>( src ), static_cast<VkCopyAccelerationStructureModeKHR>( mode ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::traceRaysNV( VULKAN_HPP_NAMESPACE::Buffer raygenShaderBindingTableBuffer, VULKAN_HPP_NAMESPACE::DeviceSize raygenShaderBindingOffset, VULKAN_HPP_NAMESPACE::Buffer missShaderBindingTableBuffer, VULKAN_HPP_NAMESPACE::DeviceSize missShaderBindingOffset, VULKAN_HPP_NAMESPACE::DeviceSize missShaderBindingStride, VULKAN_HPP_NAMESPACE::Buffer hitShaderBindingTableBuffer, VULKAN_HPP_NAMESPACE::DeviceSize hitShaderBindingOffset, VULKAN_HPP_NAMESPACE::DeviceSize hitShaderBindingStride, VULKAN_HPP_NAMESPACE::Buffer callableShaderBindingTableBuffer, VULKAN_HPP_NAMESPACE::DeviceSize callableShaderBindingOffset, VULKAN_HPP_NAMESPACE::DeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdTraceRaysNV( m_commandBuffer, static_cast<VkBuffer>( raygenShaderBindingTableBuffer ), static_cast<VkDeviceSize>( raygenShaderBindingOffset ), static_cast<VkBuffer>( missShaderBindingTableBuffer ), static_cast<VkDeviceSize>( missShaderBindingOffset ), static_cast<VkDeviceSize>( missShaderBindingStride ), static_cast<VkBuffer>( hitShaderBindingTableBuffer ), static_cast<VkDeviceSize>( hitShaderBindingOffset ), static_cast<VkDeviceSize>( hitShaderBindingStride ), static_cast<VkBuffer>( callableShaderBindingTableBuffer ), static_cast<VkDeviceSize>( callableShaderBindingOffset ), static_cast<VkDeviceSize>( callableShaderBindingStride ), width, height, depth );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createRayTracingPipelinesNV( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, uint32_t createInfoCount, const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV * pCreateInfos, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Pipeline * pPipelines, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfoCount, reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( pCreateInfos ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPipeline *>( pPipelines ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createRayTracingPipelinesNV( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesNV", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename PipelineAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, Pipeline>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createRayTracingPipelinesNV( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size(), pipelineAllocator );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesNV", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<VULKAN_HPP_NAMESPACE::Pipeline > Device::createRayTracingPipelineNV( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Pipeline  pipeline;
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    return createResultValue( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelineNV", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename PipelineAllocator>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createRayTracingPipelinesNVUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines;
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesNVUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch, typename PipelineAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<Pipeline, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createRayTracingPipelinesNVUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines( pipelineAllocator );
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesNVUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<UniqueHandle<Pipeline, Dispatch>> Device::createRayTracingPipelineNVUnique( VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoNV & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    Pipeline pipeline;
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesNV( m_device, static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkRayTracingPipelineCreateInfoNV *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<Pipeline, Dispatch>( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelineNVUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT }, deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getRayTracingShaderGroupHandlesNV( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetRayTracingShaderGroupHandlesNV( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, dataSize, pData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<DataType,Allocator>>::type Device::getRayTracingShaderGroupHandlesNV( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_ASSERT( dataSize % sizeof( DataType ) == 0 );
    std::vector<DataType,Allocator> data( dataSize / sizeof( DataType ) );
    Result result = static_cast<Result>( d.vkGetRayTracingShaderGroupHandlesNV( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, data.size() * sizeof( DataType ), reinterpret_cast<void *>( data.data() ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getRayTracingShaderGroupHandlesNV" );
  }

  template <typename DataType, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<DataType>::type Device::getRayTracingShaderGroupHandleNV( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    DataType data;
    Result result = static_cast<Result>( d.vkGetRayTracingShaderGroupHandlesNV( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, sizeof( DataType ), reinterpret_cast<void *>( &data ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getRayTracingShaderGroupHandleNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getAccelerationStructureHandleNV( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, size_t dataSize, void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetAccelerationStructureHandleNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), dataSize, pData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<DataType,Allocator>>::type Device::getAccelerationStructureHandleNV( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, size_t dataSize, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_ASSERT( dataSize % sizeof( DataType ) == 0 );
    std::vector<DataType,Allocator> data( dataSize / sizeof( DataType ) );
    Result result = static_cast<Result>( d.vkGetAccelerationStructureHandleNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), data.size() * sizeof( DataType ), reinterpret_cast<void *>( data.data() ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getAccelerationStructureHandleNV" );
  }

  template <typename DataType, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<DataType>::type Device::getAccelerationStructureHandleNV( VULKAN_HPP_NAMESPACE::AccelerationStructureNV accelerationStructure, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    DataType data;
    Result result = static_cast<Result>( d.vkGetAccelerationStructureHandleNV( m_device, static_cast<VkAccelerationStructureNV>( accelerationStructure ), sizeof( DataType ), reinterpret_cast<void *>( &data ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getAccelerationStructureHandleNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeAccelerationStructuresPropertiesNV( uint32_t accelerationStructureCount, const VULKAN_HPP_NAMESPACE::AccelerationStructureNV * pAccelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteAccelerationStructuresPropertiesNV( m_commandBuffer, accelerationStructureCount, reinterpret_cast<const VkAccelerationStructureNV *>( pAccelerationStructures ), static_cast<VkQueryType>( queryType ), static_cast<VkQueryPool>( queryPool ), firstQuery );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeAccelerationStructuresPropertiesNV( ArrayProxy<const VULKAN_HPP_NAMESPACE::AccelerationStructureNV> const & accelerationStructures, VULKAN_HPP_NAMESPACE::QueryType queryType, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdWriteAccelerationStructuresPropertiesNV( m_commandBuffer, accelerationStructures.size(), reinterpret_cast<const VkAccelerationStructureNV *>( accelerationStructures.data() ), static_cast<VkQueryType>( queryType ), static_cast<VkQueryPool>( queryPool ), firstQuery );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::compileDeferredNV( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t shader, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCompileDeferredNV( m_device, static_cast<VkPipeline>( pipeline ), shader ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::compileDeferredNV( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t shader, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCompileDeferredNV( m_device, static_cast<VkPipeline>( pipeline ), shader ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::compileDeferredNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_maintenance3 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getDescriptorSetLayoutSupportKHR( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo * pCreateInfo, VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport * pSupport, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDescriptorSetLayoutSupportKHR( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( pCreateInfo ), reinterpret_cast<VkDescriptorSetLayoutSupport *>( pSupport ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport  Device::getDescriptorSetLayoutSupportKHR( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo & createInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport  support;
    d.vkGetDescriptorSetLayoutSupportKHR( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( &createInfo ), reinterpret_cast<VkDescriptorSetLayoutSupport *>( &support ) );
    return support;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getDescriptorSetLayoutSupportKHR( const VULKAN_HPP_NAMESPACE::DescriptorSetLayoutCreateInfo & createInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport & support = structureChain.template get<VULKAN_HPP_NAMESPACE::DescriptorSetLayoutSupport>();
    d.vkGetDescriptorSetLayoutSupportKHR( m_device, reinterpret_cast<const VkDescriptorSetLayoutCreateInfo *>( &createInfo ), reinterpret_cast<VkDescriptorSetLayoutSupport *>( &support ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_draw_indirect_count ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndirectCountKHR( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndirectCountKHR( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawIndexedIndirectCountKHR( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawIndexedIndirectCountKHR( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }

  //=== VK_EXT_external_memory_host ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryHostPointerPropertiesEXT( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, const void * pHostPointer, VULKAN_HPP_NAMESPACE::MemoryHostPointerPropertiesEXT * pMemoryHostPointerProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryHostPointerPropertiesEXT( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), pHostPointer, reinterpret_cast<VkMemoryHostPointerPropertiesEXT *>( pMemoryHostPointerProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::MemoryHostPointerPropertiesEXT >::type Device::getMemoryHostPointerPropertiesEXT( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, const void * pHostPointer, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryHostPointerPropertiesEXT  memoryHostPointerProperties;
    Result result = static_cast<Result>( d.vkGetMemoryHostPointerPropertiesEXT( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), pHostPointer, reinterpret_cast<VkMemoryHostPointerPropertiesEXT *>( &memoryHostPointerProperties ) ) );
    return createResultValue( result, memoryHostPointerProperties, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryHostPointerPropertiesEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_AMD_buffer_marker ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeBufferMarkerAMD( VULKAN_HPP_NAMESPACE::PipelineStageFlagBits pipelineStage, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, VULKAN_HPP_NAMESPACE::DeviceSize dstOffset, uint32_t marker, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteBufferMarkerAMD( m_commandBuffer, static_cast<VkPipelineStageFlagBits>( pipelineStage ), static_cast<VkBuffer>( dstBuffer ), static_cast<VkDeviceSize>( dstOffset ), marker );
  }

  //=== VK_EXT_calibrated_timestamps ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getCalibrateableTimeDomainsEXT( uint32_t * pTimeDomainCount, VULKAN_HPP_NAMESPACE::TimeDomainEXT * pTimeDomains, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( m_physicalDevice, pTimeDomainCount, reinterpret_cast<VkTimeDomainEXT *>( pTimeDomains ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename TimeDomainEXTAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<TimeDomainEXT, TimeDomainEXTAllocator>>::type PhysicalDevice::getCalibrateableTimeDomainsEXT( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<TimeDomainEXT, TimeDomainEXTAllocator> timeDomains;
    uint32_t timeDomainCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( m_physicalDevice, &timeDomainCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && timeDomainCount )
      {
        timeDomains.resize( timeDomainCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( m_physicalDevice, &timeDomainCount, reinterpret_cast<VkTimeDomainEXT *>( timeDomains.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( timeDomainCount <= timeDomains.size() );
      if ( timeDomainCount < timeDomains.size() )
      {
        timeDomains.resize( timeDomainCount );
      }
    }
    return createResultValue( result, timeDomains, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getCalibrateableTimeDomainsEXT" );
  }

  template <typename TimeDomainEXTAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, TimeDomainEXT>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<TimeDomainEXT, TimeDomainEXTAllocator>>::type PhysicalDevice::getCalibrateableTimeDomainsEXT( TimeDomainEXTAllocator & timeDomainEXTAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<TimeDomainEXT, TimeDomainEXTAllocator> timeDomains( timeDomainEXTAllocator );
    uint32_t timeDomainCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( m_physicalDevice, &timeDomainCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && timeDomainCount )
      {
        timeDomains.resize( timeDomainCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( m_physicalDevice, &timeDomainCount, reinterpret_cast<VkTimeDomainEXT *>( timeDomains.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( timeDomainCount <= timeDomains.size() );
      if ( timeDomainCount < timeDomains.size() )
      {
        timeDomains.resize( timeDomainCount );
      }
    }
    return createResultValue( result, timeDomains, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getCalibrateableTimeDomainsEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getCalibratedTimestampsEXT( uint32_t timestampCount, const VULKAN_HPP_NAMESPACE::CalibratedTimestampInfoEXT * pTimestampInfos, uint64_t * pTimestamps, uint64_t * pMaxDeviation, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetCalibratedTimestampsEXT( m_device, timestampCount, reinterpret_cast<const VkCalibratedTimestampInfoEXT *>( pTimestampInfos ), pTimestamps, pMaxDeviation ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Uint64_tAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::pair<std::vector<uint64_t, Uint64_tAllocator>, uint64_t>>::type Device::getCalibratedTimestampsEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::CalibratedTimestampInfoEXT> const & timestampInfos, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::pair<std::vector<uint64_t, Uint64_tAllocator>,uint64_t> data( std::piecewise_construct, std::forward_as_tuple( timestampInfos.size() ), std::forward_as_tuple( 0 ) );
    std::vector<uint64_t, Uint64_tAllocator> & timestamps = data.first;
    uint64_t & maxDeviation = data.second;
    Result result = static_cast<Result>( d.vkGetCalibratedTimestampsEXT( m_device, timestampInfos.size(), reinterpret_cast<const VkCalibratedTimestampInfoEXT *>( timestampInfos.data() ), timestamps.data(), &maxDeviation ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getCalibratedTimestampsEXT" );
  }

  template <typename Uint64_tAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, uint64_t>::value, int>::type >
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::pair<std::vector<uint64_t, Uint64_tAllocator>, uint64_t>>::type Device::getCalibratedTimestampsEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::CalibratedTimestampInfoEXT> const & timestampInfos, Uint64_tAllocator & uint64_tAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::pair<std::vector<uint64_t, Uint64_tAllocator>,uint64_t> data( std::piecewise_construct, std::forward_as_tuple( timestampInfos.size(), uint64_tAllocator ), std::forward_as_tuple( 0 ) );
    std::vector<uint64_t, Uint64_tAllocator> & timestamps = data.first;
    uint64_t & maxDeviation = data.second;
    Result result = static_cast<Result>( d.vkGetCalibratedTimestampsEXT( m_device, timestampInfos.size(), reinterpret_cast<const VkCalibratedTimestampInfoEXT *>( timestampInfos.data() ), timestamps.data(), &maxDeviation ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getCalibratedTimestampsEXT" );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::pair<uint64_t, uint64_t>>::type Device::getCalibratedTimestampEXT( const VULKAN_HPP_NAMESPACE::CalibratedTimestampInfoEXT & timestampInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::pair<uint64_t,uint64_t> data;
    uint64_t & timestamp = data.first;
    uint64_t & maxDeviation = data.second;
    Result result = static_cast<Result>( d.vkGetCalibratedTimestampsEXT( m_device, 1, reinterpret_cast<const VkCalibratedTimestampInfoEXT *>( &timestampInfo ), &timestamp, &maxDeviation ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getCalibratedTimestampEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_mesh_shader ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMeshTasksNV( uint32_t taskCount, uint32_t firstTask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawMeshTasksNV( m_commandBuffer, taskCount, firstTask );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMeshTasksIndirectNV( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, uint32_t drawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawMeshTasksIndirectNV( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), drawCount, stride );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMeshTasksIndirectCountNV( VULKAN_HPP_NAMESPACE::Buffer buffer, VULKAN_HPP_NAMESPACE::DeviceSize offset, VULKAN_HPP_NAMESPACE::Buffer countBuffer, VULKAN_HPP_NAMESPACE::DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawMeshTasksIndirectCountNV( m_commandBuffer, static_cast<VkBuffer>( buffer ), static_cast<VkDeviceSize>( offset ), static_cast<VkBuffer>( countBuffer ), static_cast<VkDeviceSize>( countBufferOffset ), maxDrawCount, stride );
  }

  //=== VK_NV_scissor_exclusive ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setExclusiveScissorNV( uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VULKAN_HPP_NAMESPACE::Rect2D * pExclusiveScissors, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetExclusiveScissorNV( m_commandBuffer, firstExclusiveScissor, exclusiveScissorCount, reinterpret_cast<const VkRect2D *>( pExclusiveScissors ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setExclusiveScissorNV( uint32_t firstExclusiveScissor, ArrayProxy<const VULKAN_HPP_NAMESPACE::Rect2D> const & exclusiveScissors, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetExclusiveScissorNV( m_commandBuffer, firstExclusiveScissor, exclusiveScissors.size(), reinterpret_cast<const VkRect2D *>( exclusiveScissors.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_device_diagnostic_checkpoints ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setCheckpointNV( const void * pCheckpointMarker, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetCheckpointNV( m_commandBuffer, pCheckpointMarker );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename CheckpointMarkerType, typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setCheckpointNV( CheckpointMarkerType const & checkpointMarker, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetCheckpointNV( m_commandBuffer, reinterpret_cast<const void *>( &checkpointMarker ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::getCheckpointDataNV( uint32_t * pCheckpointDataCount, VULKAN_HPP_NAMESPACE::CheckpointDataNV * pCheckpointData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetQueueCheckpointDataNV( m_queue, pCheckpointDataCount, reinterpret_cast<VkCheckpointDataNV *>( pCheckpointData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename CheckpointDataNVAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<CheckpointDataNV, CheckpointDataNVAllocator> Queue::getCheckpointDataNV( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<CheckpointDataNV, CheckpointDataNVAllocator> checkpointData;
    uint32_t checkpointDataCount;
    d.vkGetQueueCheckpointDataNV( m_queue, &checkpointDataCount, nullptr );
    checkpointData.resize( checkpointDataCount );
    d.vkGetQueueCheckpointDataNV( m_queue, &checkpointDataCount, reinterpret_cast<VkCheckpointDataNV *>( checkpointData.data() ) );
    VULKAN_HPP_ASSERT( checkpointDataCount <= checkpointData.size() );
    return checkpointData;
  }

  template <typename CheckpointDataNVAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, CheckpointDataNV>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<CheckpointDataNV, CheckpointDataNVAllocator> Queue::getCheckpointDataNV( CheckpointDataNVAllocator & checkpointDataNVAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<CheckpointDataNV, CheckpointDataNVAllocator> checkpointData( checkpointDataNVAllocator );
    uint32_t checkpointDataCount;
    d.vkGetQueueCheckpointDataNV( m_queue, &checkpointDataCount, nullptr );
    checkpointData.resize( checkpointDataCount );
    d.vkGetQueueCheckpointDataNV( m_queue, &checkpointDataCount, reinterpret_cast<VkCheckpointDataNV *>( checkpointData.data() ) );
    VULKAN_HPP_ASSERT( checkpointDataCount <= checkpointData.size() );
    return checkpointData;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_timeline_semaphore ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSemaphoreCounterValueKHR( VULKAN_HPP_NAMESPACE::Semaphore semaphore, uint64_t * pValue, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSemaphoreCounterValueKHR( m_device, static_cast<VkSemaphore>( semaphore ), pValue ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<uint64_t >::type Device::getSemaphoreCounterValueKHR( VULKAN_HPP_NAMESPACE::Semaphore semaphore, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint64_t  value;
    Result result = static_cast<Result>( d.vkGetSemaphoreCounterValueKHR( m_device, static_cast<VkSemaphore>( semaphore ), &value ) );
    return createResultValue( result, value, VULKAN_HPP_NAMESPACE_STRING "::Device::getSemaphoreCounterValueKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitSemaphoresKHR( const VULKAN_HPP_NAMESPACE::SemaphoreWaitInfo * pWaitInfo, uint64_t timeout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkWaitSemaphoresKHR( m_device, reinterpret_cast<const VkSemaphoreWaitInfo *>( pWaitInfo ), timeout ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitSemaphoresKHR( const VULKAN_HPP_NAMESPACE::SemaphoreWaitInfo & waitInfo, uint64_t timeout, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkWaitSemaphoresKHR( m_device, reinterpret_cast<const VkSemaphoreWaitInfo *>( &waitInfo ), timeout ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::waitSemaphoresKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eTimeout } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::signalSemaphoreKHR( const VULKAN_HPP_NAMESPACE::SemaphoreSignalInfo * pSignalInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSignalSemaphoreKHR( m_device, reinterpret_cast<const VkSemaphoreSignalInfo *>( pSignalInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::signalSemaphoreKHR( const VULKAN_HPP_NAMESPACE::SemaphoreSignalInfo & signalInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSignalSemaphoreKHR( m_device, reinterpret_cast<const VkSemaphoreSignalInfo *>( &signalInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::signalSemaphoreKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_INTEL_performance_query ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::initializePerformanceApiINTEL( const VULKAN_HPP_NAMESPACE::InitializePerformanceApiInfoINTEL * pInitializeInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkInitializePerformanceApiINTEL( m_device, reinterpret_cast<const VkInitializePerformanceApiInfoINTEL *>( pInitializeInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::initializePerformanceApiINTEL( const VULKAN_HPP_NAMESPACE::InitializePerformanceApiInfoINTEL & initializeInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkInitializePerformanceApiINTEL( m_device, reinterpret_cast<const VkInitializePerformanceApiInfoINTEL *>( &initializeInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::initializePerformanceApiINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::uninitializePerformanceApiINTEL( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkUninitializePerformanceApiINTEL( m_device );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result CommandBuffer::setPerformanceMarkerINTEL( const VULKAN_HPP_NAMESPACE::PerformanceMarkerInfoINTEL * pMarkerInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCmdSetPerformanceMarkerINTEL( m_commandBuffer, reinterpret_cast<const VkPerformanceMarkerInfoINTEL *>( pMarkerInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type CommandBuffer::setPerformanceMarkerINTEL( const VULKAN_HPP_NAMESPACE::PerformanceMarkerInfoINTEL & markerInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCmdSetPerformanceMarkerINTEL( m_commandBuffer, reinterpret_cast<const VkPerformanceMarkerInfoINTEL *>( &markerInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::setPerformanceMarkerINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result CommandBuffer::setPerformanceStreamMarkerINTEL( const VULKAN_HPP_NAMESPACE::PerformanceStreamMarkerInfoINTEL * pMarkerInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCmdSetPerformanceStreamMarkerINTEL( m_commandBuffer, reinterpret_cast<const VkPerformanceStreamMarkerInfoINTEL *>( pMarkerInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type CommandBuffer::setPerformanceStreamMarkerINTEL( const VULKAN_HPP_NAMESPACE::PerformanceStreamMarkerInfoINTEL & markerInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCmdSetPerformanceStreamMarkerINTEL( m_commandBuffer, reinterpret_cast<const VkPerformanceStreamMarkerInfoINTEL *>( &markerInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::setPerformanceStreamMarkerINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result CommandBuffer::setPerformanceOverrideINTEL( const VULKAN_HPP_NAMESPACE::PerformanceOverrideInfoINTEL * pOverrideInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCmdSetPerformanceOverrideINTEL( m_commandBuffer, reinterpret_cast<const VkPerformanceOverrideInfoINTEL *>( pOverrideInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type CommandBuffer::setPerformanceOverrideINTEL( const VULKAN_HPP_NAMESPACE::PerformanceOverrideInfoINTEL & overrideInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkCmdSetPerformanceOverrideINTEL( m_commandBuffer, reinterpret_cast<const VkPerformanceOverrideInfoINTEL *>( &overrideInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::setPerformanceOverrideINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::acquirePerformanceConfigurationINTEL( const VULKAN_HPP_NAMESPACE::PerformanceConfigurationAcquireInfoINTEL * pAcquireInfo, VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL * pConfiguration, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquirePerformanceConfigurationINTEL( m_device, reinterpret_cast<const VkPerformanceConfigurationAcquireInfoINTEL *>( pAcquireInfo ), reinterpret_cast<VkPerformanceConfigurationINTEL *>( pConfiguration ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL >::type Device::acquirePerformanceConfigurationINTEL( const VULKAN_HPP_NAMESPACE::PerformanceConfigurationAcquireInfoINTEL & acquireInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL  configuration;
    Result result = static_cast<Result>( d.vkAcquirePerformanceConfigurationINTEL( m_device, reinterpret_cast<const VkPerformanceConfigurationAcquireInfoINTEL *>( &acquireInfo ), reinterpret_cast<VkPerformanceConfigurationINTEL *>( &configuration ) ) );
    return createResultValue( result, configuration, VULKAN_HPP_NAMESPACE_STRING "::Device::acquirePerformanceConfigurationINTEL" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL, Dispatch>>::type Device::acquirePerformanceConfigurationINTELUnique( const VULKAN_HPP_NAMESPACE::PerformanceConfigurationAcquireInfoINTEL & acquireInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration;
    Result result = static_cast<Result>( d.vkAcquirePerformanceConfigurationINTEL( m_device, reinterpret_cast<const VkPerformanceConfigurationAcquireInfoINTEL *>( &acquireInfo ), reinterpret_cast<VkPerformanceConfigurationINTEL *>( &configuration ) ) );
    ObjectRelease<Device, Dispatch> deleter( *this, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL, Dispatch>( result, configuration, VULKAN_HPP_NAMESPACE_STRING "::Device::acquirePerformanceConfigurationINTELUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::releasePerformanceConfigurationINTEL( VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkReleasePerformanceConfigurationINTEL( m_device, static_cast<VkPerformanceConfigurationINTEL>( configuration ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::releasePerformanceConfigurationINTEL( VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkReleasePerformanceConfigurationINTEL( m_device, static_cast<VkPerformanceConfigurationINTEL>( configuration ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::releasePerformanceConfigurationINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::release( VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkReleasePerformanceConfigurationINTEL( m_device, static_cast<VkPerformanceConfigurationINTEL>( configuration ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::release( VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkReleasePerformanceConfigurationINTEL( m_device, static_cast<VkPerformanceConfigurationINTEL>( configuration ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::release" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::setPerformanceConfigurationINTEL( VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueueSetPerformanceConfigurationINTEL( m_queue, static_cast<VkPerformanceConfigurationINTEL>( configuration ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Queue::setPerformanceConfigurationINTEL( VULKAN_HPP_NAMESPACE::PerformanceConfigurationINTEL configuration, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueueSetPerformanceConfigurationINTEL( m_queue, static_cast<VkPerformanceConfigurationINTEL>( configuration ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::setPerformanceConfigurationINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getPerformanceParameterINTEL( VULKAN_HPP_NAMESPACE::PerformanceParameterTypeINTEL parameter, VULKAN_HPP_NAMESPACE::PerformanceValueINTEL * pValue, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPerformanceParameterINTEL( m_device, static_cast<VkPerformanceParameterTypeINTEL>( parameter ), reinterpret_cast<VkPerformanceValueINTEL *>( pValue ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::PerformanceValueINTEL >::type Device::getPerformanceParameterINTEL( VULKAN_HPP_NAMESPACE::PerformanceParameterTypeINTEL parameter, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PerformanceValueINTEL  value;
    Result result = static_cast<Result>( d.vkGetPerformanceParameterINTEL( m_device, static_cast<VkPerformanceParameterTypeINTEL>( parameter ), reinterpret_cast<VkPerformanceValueINTEL *>( &value ) ) );
    return createResultValue( result, value, VULKAN_HPP_NAMESPACE_STRING "::Device::getPerformanceParameterINTEL" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_AMD_display_native_hdr ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::setLocalDimmingAMD( VULKAN_HPP_NAMESPACE::SwapchainKHR swapChain, VULKAN_HPP_NAMESPACE::Bool32 localDimmingEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkSetLocalDimmingAMD( m_device, static_cast<VkSwapchainKHR>( swapChain ), static_cast<VkBool32>( localDimmingEnable ) );
  }

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_imagepipe_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createImagePipeSurfaceFUCHSIA( const VULKAN_HPP_NAMESPACE::ImagePipeSurfaceCreateInfoFUCHSIA * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateImagePipeSurfaceFUCHSIA( m_instance, reinterpret_cast<const VkImagePipeSurfaceCreateInfoFUCHSIA *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createImagePipeSurfaceFUCHSIA( const VULKAN_HPP_NAMESPACE::ImagePipeSurfaceCreateInfoFUCHSIA & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateImagePipeSurfaceFUCHSIA( m_instance, reinterpret_cast<const VkImagePipeSurfaceCreateInfoFUCHSIA *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createImagePipeSurfaceFUCHSIA" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createImagePipeSurfaceFUCHSIAUnique( const VULKAN_HPP_NAMESPACE::ImagePipeSurfaceCreateInfoFUCHSIA & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateImagePipeSurfaceFUCHSIA( m_instance, reinterpret_cast<const VkImagePipeSurfaceCreateInfoFUCHSIA *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createImagePipeSurfaceFUCHSIAUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_METAL_EXT )
  //=== VK_EXT_metal_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createMetalSurfaceEXT( const VULKAN_HPP_NAMESPACE::MetalSurfaceCreateInfoEXT * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateMetalSurfaceEXT( m_instance, reinterpret_cast<const VkMetalSurfaceCreateInfoEXT *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createMetalSurfaceEXT( const VULKAN_HPP_NAMESPACE::MetalSurfaceCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateMetalSurfaceEXT( m_instance, reinterpret_cast<const VkMetalSurfaceCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createMetalSurfaceEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createMetalSurfaceEXTUnique( const VULKAN_HPP_NAMESPACE::MetalSurfaceCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateMetalSurfaceEXT( m_instance, reinterpret_cast<const VkMetalSurfaceCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createMetalSurfaceEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_METAL_EXT*/

  //=== VK_KHR_fragment_shading_rate ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getFragmentShadingRatesKHR( uint32_t * pFragmentShadingRateCount, VULKAN_HPP_NAMESPACE::PhysicalDeviceFragmentShadingRateKHR * pFragmentShadingRates, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceFragmentShadingRatesKHR( m_physicalDevice, pFragmentShadingRateCount, reinterpret_cast<VkPhysicalDeviceFragmentShadingRateKHR *>( pFragmentShadingRates ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PhysicalDeviceFragmentShadingRateKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceFragmentShadingRateKHR, PhysicalDeviceFragmentShadingRateKHRAllocator>>::type PhysicalDevice::getFragmentShadingRatesKHR( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceFragmentShadingRateKHR, PhysicalDeviceFragmentShadingRateKHRAllocator> fragmentShadingRates;
    uint32_t fragmentShadingRateCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceFragmentShadingRatesKHR( m_physicalDevice, &fragmentShadingRateCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && fragmentShadingRateCount )
      {
        fragmentShadingRates.resize( fragmentShadingRateCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceFragmentShadingRatesKHR( m_physicalDevice, &fragmentShadingRateCount, reinterpret_cast<VkPhysicalDeviceFragmentShadingRateKHR *>( fragmentShadingRates.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( fragmentShadingRateCount <= fragmentShadingRates.size() );
      if ( fragmentShadingRateCount < fragmentShadingRates.size() )
      {
        fragmentShadingRates.resize( fragmentShadingRateCount );
      }
    }
    return createResultValue( result, fragmentShadingRates, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getFragmentShadingRatesKHR" );
  }

  template <typename PhysicalDeviceFragmentShadingRateKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PhysicalDeviceFragmentShadingRateKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceFragmentShadingRateKHR, PhysicalDeviceFragmentShadingRateKHRAllocator>>::type PhysicalDevice::getFragmentShadingRatesKHR( PhysicalDeviceFragmentShadingRateKHRAllocator & physicalDeviceFragmentShadingRateKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceFragmentShadingRateKHR, PhysicalDeviceFragmentShadingRateKHRAllocator> fragmentShadingRates( physicalDeviceFragmentShadingRateKHRAllocator );
    uint32_t fragmentShadingRateCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceFragmentShadingRatesKHR( m_physicalDevice, &fragmentShadingRateCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && fragmentShadingRateCount )
      {
        fragmentShadingRates.resize( fragmentShadingRateCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceFragmentShadingRatesKHR( m_physicalDevice, &fragmentShadingRateCount, reinterpret_cast<VkPhysicalDeviceFragmentShadingRateKHR *>( fragmentShadingRates.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( fragmentShadingRateCount <= fragmentShadingRates.size() );
      if ( fragmentShadingRateCount < fragmentShadingRates.size() )
      {
        fragmentShadingRates.resize( fragmentShadingRateCount );
      }
    }
    return createResultValue( result, fragmentShadingRates, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getFragmentShadingRatesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setFragmentShadingRateKHR( const VULKAN_HPP_NAMESPACE::Extent2D * pFragmentSize, const VULKAN_HPP_NAMESPACE::FragmentShadingRateCombinerOpKHR combinerOps[2], Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetFragmentShadingRateKHR( m_commandBuffer, reinterpret_cast<const VkExtent2D *>( pFragmentSize ), reinterpret_cast<const VkFragmentShadingRateCombinerOpKHR *>( combinerOps ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setFragmentShadingRateKHR( const VULKAN_HPP_NAMESPACE::Extent2D & fragmentSize, const VULKAN_HPP_NAMESPACE::FragmentShadingRateCombinerOpKHR combinerOps[2], Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetFragmentShadingRateKHR( m_commandBuffer, reinterpret_cast<const VkExtent2D *>( &fragmentSize ), reinterpret_cast<const VkFragmentShadingRateCombinerOpKHR *>( combinerOps ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_buffer_device_address ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getBufferAddressEXT( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<DeviceAddress>( d.vkGetBufferDeviceAddressEXT( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getBufferAddressEXT( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetBufferDeviceAddressEXT( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_tooling_info ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getToolPropertiesEXT( uint32_t * pToolCount, VULKAN_HPP_NAMESPACE::PhysicalDeviceToolProperties * pToolProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceToolPropertiesEXT( m_physicalDevice, pToolCount, reinterpret_cast<VkPhysicalDeviceToolProperties *>( pToolProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PhysicalDeviceToolPropertiesAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator>>::type PhysicalDevice::getToolPropertiesEXT( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator> toolProperties;
    uint32_t toolCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceToolPropertiesEXT( m_physicalDevice, &toolCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && toolCount )
      {
        toolProperties.resize( toolCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceToolPropertiesEXT( m_physicalDevice, &toolCount, reinterpret_cast<VkPhysicalDeviceToolProperties *>( toolProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( toolCount <= toolProperties.size() );
      if ( toolCount < toolProperties.size() )
      {
        toolProperties.resize( toolCount );
      }
    }
    return createResultValue( result, toolProperties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getToolPropertiesEXT" );
  }

  template <typename PhysicalDeviceToolPropertiesAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PhysicalDeviceToolProperties>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator>>::type PhysicalDevice::getToolPropertiesEXT( PhysicalDeviceToolPropertiesAllocator & physicalDeviceToolPropertiesAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PhysicalDeviceToolProperties, PhysicalDeviceToolPropertiesAllocator> toolProperties( physicalDeviceToolPropertiesAllocator );
    uint32_t toolCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceToolPropertiesEXT( m_physicalDevice, &toolCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && toolCount )
      {
        toolProperties.resize( toolCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceToolPropertiesEXT( m_physicalDevice, &toolCount, reinterpret_cast<VkPhysicalDeviceToolProperties *>( toolProperties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( toolCount <= toolProperties.size() );
      if ( toolCount < toolProperties.size() )
      {
        toolProperties.resize( toolCount );
      }
    }
    return createResultValue( result, toolProperties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getToolPropertiesEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_present_wait ===


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitForPresentKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, uint64_t presentId, uint64_t timeout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkWaitForPresentKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), presentId, timeout ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::waitForPresentKHR( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, uint64_t presentId, uint64_t timeout, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkWaitForPresentKHR( m_device, static_cast<VkSwapchainKHR>( swapchain ), presentId, timeout ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::waitForPresentKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eTimeout } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_cooperative_matrix ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getCooperativeMatrixPropertiesNV( uint32_t * pPropertyCount, VULKAN_HPP_NAMESPACE::CooperativeMatrixPropertiesNV * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( m_physicalDevice, pPropertyCount, reinterpret_cast<VkCooperativeMatrixPropertiesNV *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename CooperativeMatrixPropertiesNVAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<CooperativeMatrixPropertiesNV, CooperativeMatrixPropertiesNVAllocator>>::type PhysicalDevice::getCooperativeMatrixPropertiesNV( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<CooperativeMatrixPropertiesNV, CooperativeMatrixPropertiesNVAllocator> properties;
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( m_physicalDevice, &propertyCount, reinterpret_cast<VkCooperativeMatrixPropertiesNV *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getCooperativeMatrixPropertiesNV" );
  }

  template <typename CooperativeMatrixPropertiesNVAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, CooperativeMatrixPropertiesNV>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<CooperativeMatrixPropertiesNV, CooperativeMatrixPropertiesNVAllocator>>::type PhysicalDevice::getCooperativeMatrixPropertiesNV( CooperativeMatrixPropertiesNVAllocator & cooperativeMatrixPropertiesNVAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<CooperativeMatrixPropertiesNV, CooperativeMatrixPropertiesNVAllocator> properties( cooperativeMatrixPropertiesNVAllocator );
    uint32_t propertyCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( m_physicalDevice, &propertyCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && propertyCount )
      {
        properties.resize( propertyCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( m_physicalDevice, &propertyCount, reinterpret_cast<VkCooperativeMatrixPropertiesNV *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( propertyCount <= properties.size() );
      if ( propertyCount < properties.size() )
      {
        properties.resize( propertyCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getCooperativeMatrixPropertiesNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_coverage_reduction_mode ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSupportedFramebufferMixedSamplesCombinationsNV( uint32_t * pCombinationCount, VULKAN_HPP_NAMESPACE::FramebufferMixedSamplesCombinationNV * pCombinations, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV( m_physicalDevice, pCombinationCount, reinterpret_cast<VkFramebufferMixedSamplesCombinationNV *>( pCombinations ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename FramebufferMixedSamplesCombinationNVAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<FramebufferMixedSamplesCombinationNV, FramebufferMixedSamplesCombinationNVAllocator>>::type PhysicalDevice::getSupportedFramebufferMixedSamplesCombinationsNV( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<FramebufferMixedSamplesCombinationNV, FramebufferMixedSamplesCombinationNVAllocator> combinations;
    uint32_t combinationCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV( m_physicalDevice, &combinationCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && combinationCount )
      {
        combinations.resize( combinationCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV( m_physicalDevice, &combinationCount, reinterpret_cast<VkFramebufferMixedSamplesCombinationNV *>( combinations.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( combinationCount <= combinations.size() );
      if ( combinationCount < combinations.size() )
      {
        combinations.resize( combinationCount );
      }
    }
    return createResultValue( result, combinations, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSupportedFramebufferMixedSamplesCombinationsNV" );
  }

  template <typename FramebufferMixedSamplesCombinationNVAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, FramebufferMixedSamplesCombinationNV>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<FramebufferMixedSamplesCombinationNV, FramebufferMixedSamplesCombinationNVAllocator>>::type PhysicalDevice::getSupportedFramebufferMixedSamplesCombinationsNV( FramebufferMixedSamplesCombinationNVAllocator & framebufferMixedSamplesCombinationNVAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<FramebufferMixedSamplesCombinationNV, FramebufferMixedSamplesCombinationNVAllocator> combinations( framebufferMixedSamplesCombinationNVAllocator );
    uint32_t combinationCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV( m_physicalDevice, &combinationCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && combinationCount )
      {
        combinations.resize( combinationCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV( m_physicalDevice, &combinationCount, reinterpret_cast<VkFramebufferMixedSamplesCombinationNV *>( combinations.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( combinationCount <= combinations.size() );
      if ( combinationCount < combinations.size() )
      {
        combinations.resize( combinationCount );
      }
    }
    return createResultValue( result, combinations, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSupportedFramebufferMixedSamplesCombinationsNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_EXT_full_screen_exclusive ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getSurfacePresentModes2EXT( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR * pSurfaceInfo, uint32_t * pPresentModeCount, VULKAN_HPP_NAMESPACE::PresentModeKHR * pPresentModes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModes2EXT( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( pSurfaceInfo ), pPresentModeCount, reinterpret_cast<VkPresentModeKHR *>( pPresentModes ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PresentModeKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PresentModeKHR, PresentModeKHRAllocator>>::type PhysicalDevice::getSurfacePresentModes2EXT( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PresentModeKHR, PresentModeKHRAllocator> presentModes;
    uint32_t presentModeCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModes2EXT( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &presentModeCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && presentModeCount )
      {
        presentModes.resize( presentModeCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModes2EXT( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &presentModeCount, reinterpret_cast<VkPresentModeKHR *>( presentModes.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( presentModeCount <= presentModes.size() );
      if ( presentModeCount < presentModes.size() )
      {
        presentModes.resize( presentModeCount );
      }
    }
    return createResultValue( result, presentModes, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfacePresentModes2EXT" );
  }

  template <typename PresentModeKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PresentModeKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PresentModeKHR, PresentModeKHRAllocator>>::type PhysicalDevice::getSurfacePresentModes2EXT( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, PresentModeKHRAllocator & presentModeKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PresentModeKHR, PresentModeKHRAllocator> presentModes( presentModeKHRAllocator );
    uint32_t presentModeCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModes2EXT( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &presentModeCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && presentModeCount )
      {
        presentModes.resize( presentModeCount );
        result = static_cast<Result>( d.vkGetPhysicalDeviceSurfacePresentModes2EXT( m_physicalDevice, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), &presentModeCount, reinterpret_cast<VkPresentModeKHR *>( presentModes.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( presentModeCount <= presentModes.size() );
      if ( presentModeCount < presentModes.size() )
      {
        presentModes.resize( presentModeCount );
      }
    }
    return createResultValue( result, presentModes, VULKAN_HPP_NAMESPACE_STRING"::PhysicalDevice::getSurfacePresentModes2EXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::acquireFullScreenExclusiveModeEXT( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireFullScreenExclusiveModeEXT( m_device, static_cast<VkSwapchainKHR>( swapchain ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::acquireFullScreenExclusiveModeEXT( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkAcquireFullScreenExclusiveModeEXT( m_device, static_cast<VkSwapchainKHR>( swapchain ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::acquireFullScreenExclusiveModeEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::releaseFullScreenExclusiveModeEXT( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkReleaseFullScreenExclusiveModeEXT( m_device, static_cast<VkSwapchainKHR>( swapchain ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::releaseFullScreenExclusiveModeEXT( VULKAN_HPP_NAMESPACE::SwapchainKHR swapchain, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkReleaseFullScreenExclusiveModeEXT( m_device, static_cast<VkSwapchainKHR>( swapchain ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::releaseFullScreenExclusiveModeEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getGroupSurfacePresentModes2EXT( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR * pSurfaceInfo, VULKAN_HPP_NAMESPACE::DeviceGroupPresentModeFlagsKHR * pModes, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDeviceGroupSurfacePresentModes2EXT( m_device, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( pSurfaceInfo ), reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR *>( pModes ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DeviceGroupPresentModeFlagsKHR >::type Device::getGroupSurfacePresentModes2EXT( const VULKAN_HPP_NAMESPACE::PhysicalDeviceSurfaceInfo2KHR & surfaceInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DeviceGroupPresentModeFlagsKHR  modes;
    Result result = static_cast<Result>( d.vkGetDeviceGroupSurfacePresentModes2EXT( m_device, reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR *>( &surfaceInfo ), reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR *>( &modes ) ) );
    return createResultValue( result, modes, VULKAN_HPP_NAMESPACE_STRING "::Device::getGroupSurfacePresentModes2EXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_headless_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createHeadlessSurfaceEXT( const VULKAN_HPP_NAMESPACE::HeadlessSurfaceCreateInfoEXT * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateHeadlessSurfaceEXT( m_instance, reinterpret_cast<const VkHeadlessSurfaceCreateInfoEXT *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createHeadlessSurfaceEXT( const VULKAN_HPP_NAMESPACE::HeadlessSurfaceCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateHeadlessSurfaceEXT( m_instance, reinterpret_cast<const VkHeadlessSurfaceCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createHeadlessSurfaceEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createHeadlessSurfaceEXTUnique( const VULKAN_HPP_NAMESPACE::HeadlessSurfaceCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateHeadlessSurfaceEXT( m_instance, reinterpret_cast<const VkHeadlessSurfaceCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createHeadlessSurfaceEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_buffer_device_address ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getBufferAddressKHR( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<DeviceAddress>( d.vkGetBufferDeviceAddressKHR( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( pInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceAddress Device::getBufferAddressKHR( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetBufferDeviceAddressKHR( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getBufferOpaqueCaptureAddressKHR( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetBufferOpaqueCaptureAddressKHR( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getBufferOpaqueCaptureAddressKHR( const VULKAN_HPP_NAMESPACE::BufferDeviceAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetBufferOpaqueCaptureAddressKHR( m_device, reinterpret_cast<const VkBufferDeviceAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getMemoryOpaqueCaptureAddressKHR( const VULKAN_HPP_NAMESPACE::DeviceMemoryOpaqueCaptureAddressInfo * pInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetDeviceMemoryOpaqueCaptureAddressKHR( m_device, reinterpret_cast<const VkDeviceMemoryOpaqueCaptureAddressInfo *>( pInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE uint64_t Device::getMemoryOpaqueCaptureAddressKHR( const VULKAN_HPP_NAMESPACE::DeviceMemoryOpaqueCaptureAddressInfo & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetDeviceMemoryOpaqueCaptureAddressKHR( m_device, reinterpret_cast<const VkDeviceMemoryOpaqueCaptureAddressInfo *>( &info ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_line_rasterization ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setLineStippleEXT( uint32_t lineStippleFactor, uint16_t lineStipplePattern, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetLineStippleEXT( m_commandBuffer, lineStippleFactor, lineStipplePattern );
  }

  //=== VK_EXT_host_query_reset ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::resetQueryPoolEXT( VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkResetQueryPoolEXT( m_device, static_cast<VkQueryPool>( queryPool ), firstQuery, queryCount );
  }

  //=== VK_EXT_extended_dynamic_state ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setCullModeEXT( VULKAN_HPP_NAMESPACE::CullModeFlags cullMode, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetCullModeEXT( m_commandBuffer, static_cast<VkCullModeFlags>( cullMode ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setFrontFaceEXT( VULKAN_HPP_NAMESPACE::FrontFace frontFace, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetFrontFaceEXT( m_commandBuffer, static_cast<VkFrontFace>( frontFace ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setPrimitiveTopologyEXT( VULKAN_HPP_NAMESPACE::PrimitiveTopology primitiveTopology, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetPrimitiveTopologyEXT( m_commandBuffer, static_cast<VkPrimitiveTopology>( primitiveTopology ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportWithCountEXT( uint32_t viewportCount, const VULKAN_HPP_NAMESPACE::Viewport * pViewports, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetViewportWithCountEXT( m_commandBuffer, viewportCount, reinterpret_cast<const VkViewport *>( pViewports ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setViewportWithCountEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::Viewport> const & viewports, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetViewportWithCountEXT( m_commandBuffer, viewports.size(), reinterpret_cast<const VkViewport *>( viewports.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setScissorWithCountEXT( uint32_t scissorCount, const VULKAN_HPP_NAMESPACE::Rect2D * pScissors, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetScissorWithCountEXT( m_commandBuffer, scissorCount, reinterpret_cast<const VkRect2D *>( pScissors ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setScissorWithCountEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::Rect2D> const & scissors, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetScissorWithCountEXT( m_commandBuffer, scissors.size(), reinterpret_cast<const VkRect2D *>( scissors.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindVertexBuffers2EXT( uint32_t firstBinding, uint32_t bindingCount, const VULKAN_HPP_NAMESPACE::Buffer * pBuffers, const VULKAN_HPP_NAMESPACE::DeviceSize * pOffsets, const VULKAN_HPP_NAMESPACE::DeviceSize * pSizes, const VULKAN_HPP_NAMESPACE::DeviceSize * pStrides, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindVertexBuffers2EXT( m_commandBuffer, firstBinding, bindingCount, reinterpret_cast<const VkBuffer *>( pBuffers ), reinterpret_cast<const VkDeviceSize *>( pOffsets ), reinterpret_cast<const VkDeviceSize *>( pSizes ), reinterpret_cast<const VkDeviceSize *>( pStrides ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindVertexBuffers2EXT( uint32_t firstBinding, ArrayProxy<const VULKAN_HPP_NAMESPACE::Buffer> const & buffers, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & offsets, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & sizes, ArrayProxy<const VULKAN_HPP_NAMESPACE::DeviceSize> const & strides, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( buffers.size() == offsets.size() );
    VULKAN_HPP_ASSERT( sizes.empty() || buffers.size() == sizes.size() );
    VULKAN_HPP_ASSERT( strides.empty() || buffers.size() == strides.size() );
#else
    if ( buffers.size() != offsets.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers2EXT: buffers.size() != offsets.size()" );
  }
    if ( !sizes.empty() && buffers.size() != sizes.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers2EXT: buffers.size() != sizes.size()" );
  }
    if ( !strides.empty() && buffers.size() != strides.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::bindVertexBuffers2EXT: buffers.size() != strides.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdBindVertexBuffers2EXT( m_commandBuffer, firstBinding, buffers.size(), reinterpret_cast<const VkBuffer *>( buffers.data() ), reinterpret_cast<const VkDeviceSize *>( offsets.data() ), reinterpret_cast<const VkDeviceSize *>( sizes.data() ), reinterpret_cast<const VkDeviceSize *>( strides.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthTestEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 depthTestEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthTestEnableEXT( m_commandBuffer, static_cast<VkBool32>( depthTestEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthWriteEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 depthWriteEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthWriteEnableEXT( m_commandBuffer, static_cast<VkBool32>( depthWriteEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthCompareOpEXT( VULKAN_HPP_NAMESPACE::CompareOp depthCompareOp, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthCompareOpEXT( m_commandBuffer, static_cast<VkCompareOp>( depthCompareOp ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthBoundsTestEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 depthBoundsTestEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthBoundsTestEnableEXT( m_commandBuffer, static_cast<VkBool32>( depthBoundsTestEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilTestEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 stencilTestEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilTestEnableEXT( m_commandBuffer, static_cast<VkBool32>( stencilTestEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setStencilOpEXT( VULKAN_HPP_NAMESPACE::StencilFaceFlags faceMask, VULKAN_HPP_NAMESPACE::StencilOp failOp, VULKAN_HPP_NAMESPACE::StencilOp passOp, VULKAN_HPP_NAMESPACE::StencilOp depthFailOp, VULKAN_HPP_NAMESPACE::CompareOp compareOp, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetStencilOpEXT( m_commandBuffer, static_cast<VkStencilFaceFlags>( faceMask ), static_cast<VkStencilOp>( failOp ), static_cast<VkStencilOp>( passOp ), static_cast<VkStencilOp>( depthFailOp ), static_cast<VkCompareOp>( compareOp ) );
  }

  //=== VK_KHR_deferred_host_operations ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createDeferredOperationKHR( const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::DeferredOperationKHR * pDeferredOperation, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDeferredOperationKHR( m_device, reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkDeferredOperationKHR *>( pDeferredOperation ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DeferredOperationKHR >::type Device::createDeferredOperationKHR( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DeferredOperationKHR  deferredOperation;
    Result result = static_cast<Result>( d.vkCreateDeferredOperationKHR( m_device, reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDeferredOperationKHR *>( &deferredOperation ) ) );
    return createResultValue( result, deferredOperation, VULKAN_HPP_NAMESPACE_STRING "::Device::createDeferredOperationKHR" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DeferredOperationKHR, Dispatch>>::type Device::createDeferredOperationKHRUnique( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation;
    Result result = static_cast<Result>( d.vkCreateDeferredOperationKHR( m_device, reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkDeferredOperationKHR *>( &deferredOperation ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DeferredOperationKHR, Dispatch>( result, deferredOperation, VULKAN_HPP_NAMESPACE_STRING "::Device::createDeferredOperationKHRUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDeferredOperationKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDeferredOperationKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyDeferredOperationKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDeferredOperationKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyDeferredOperationKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyDeferredOperationKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE uint32_t Device::getDeferredOperationMaxConcurrencyKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return d.vkGetDeferredOperationMaxConcurrencyKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ) );
  }


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getDeferredOperationResultKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDeferredOperationResultKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getDeferredOperationResultKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkGetDeferredOperationResultKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::getDeferredOperationResultKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eNotReady } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::deferredOperationJoinKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkDeferredOperationJoinKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::deferredOperationJoinKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR operation, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkDeferredOperationJoinKHR( m_device, static_cast<VkDeferredOperationKHR>( operation ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::deferredOperationJoinKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eThreadDoneKHR, VULKAN_HPP_NAMESPACE::Result::eThreadIdleKHR } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_KHR_pipeline_executable_properties ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getPipelineExecutablePropertiesKHR( const VULKAN_HPP_NAMESPACE::PipelineInfoKHR * pPipelineInfo, uint32_t * pExecutableCount, VULKAN_HPP_NAMESPACE::PipelineExecutablePropertiesKHR * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPipelineExecutablePropertiesKHR( m_device, reinterpret_cast<const VkPipelineInfoKHR *>( pPipelineInfo ), pExecutableCount, reinterpret_cast<VkPipelineExecutablePropertiesKHR *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineExecutablePropertiesKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PipelineExecutablePropertiesKHR, PipelineExecutablePropertiesKHRAllocator>>::type Device::getPipelineExecutablePropertiesKHR( const VULKAN_HPP_NAMESPACE::PipelineInfoKHR & pipelineInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PipelineExecutablePropertiesKHR, PipelineExecutablePropertiesKHRAllocator> properties;
    uint32_t executableCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineExecutablePropertiesKHR( m_device, reinterpret_cast<const VkPipelineInfoKHR *>( &pipelineInfo ), &executableCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && executableCount )
      {
        properties.resize( executableCount );
        result = static_cast<Result>( d.vkGetPipelineExecutablePropertiesKHR( m_device, reinterpret_cast<const VkPipelineInfoKHR *>( &pipelineInfo ), &executableCount, reinterpret_cast<VkPipelineExecutablePropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( executableCount <= properties.size() );
      if ( executableCount < properties.size() )
      {
        properties.resize( executableCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineExecutablePropertiesKHR" );
  }

  template <typename PipelineExecutablePropertiesKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PipelineExecutablePropertiesKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PipelineExecutablePropertiesKHR, PipelineExecutablePropertiesKHRAllocator>>::type Device::getPipelineExecutablePropertiesKHR( const VULKAN_HPP_NAMESPACE::PipelineInfoKHR & pipelineInfo, PipelineExecutablePropertiesKHRAllocator & pipelineExecutablePropertiesKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PipelineExecutablePropertiesKHR, PipelineExecutablePropertiesKHRAllocator> properties( pipelineExecutablePropertiesKHRAllocator );
    uint32_t executableCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineExecutablePropertiesKHR( m_device, reinterpret_cast<const VkPipelineInfoKHR *>( &pipelineInfo ), &executableCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && executableCount )
      {
        properties.resize( executableCount );
        result = static_cast<Result>( d.vkGetPipelineExecutablePropertiesKHR( m_device, reinterpret_cast<const VkPipelineInfoKHR *>( &pipelineInfo ), &executableCount, reinterpret_cast<VkPipelineExecutablePropertiesKHR *>( properties.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( executableCount <= properties.size() );
      if ( executableCount < properties.size() )
      {
        properties.resize( executableCount );
      }
    }
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineExecutablePropertiesKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getPipelineExecutableStatisticsKHR( const VULKAN_HPP_NAMESPACE::PipelineExecutableInfoKHR * pExecutableInfo, uint32_t * pStatisticCount, VULKAN_HPP_NAMESPACE::PipelineExecutableStatisticKHR * pStatistics, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPipelineExecutableStatisticsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( pExecutableInfo ), pStatisticCount, reinterpret_cast<VkPipelineExecutableStatisticKHR *>( pStatistics ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineExecutableStatisticKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PipelineExecutableStatisticKHR, PipelineExecutableStatisticKHRAllocator>>::type Device::getPipelineExecutableStatisticsKHR( const VULKAN_HPP_NAMESPACE::PipelineExecutableInfoKHR & executableInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PipelineExecutableStatisticKHR, PipelineExecutableStatisticKHRAllocator> statistics;
    uint32_t statisticCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineExecutableStatisticsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &statisticCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && statisticCount )
      {
        statistics.resize( statisticCount );
        result = static_cast<Result>( d.vkGetPipelineExecutableStatisticsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &statisticCount, reinterpret_cast<VkPipelineExecutableStatisticKHR *>( statistics.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( statisticCount <= statistics.size() );
      if ( statisticCount < statistics.size() )
      {
        statistics.resize( statisticCount );
      }
    }
    return createResultValue( result, statistics, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineExecutableStatisticsKHR" );
  }

  template <typename PipelineExecutableStatisticKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PipelineExecutableStatisticKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PipelineExecutableStatisticKHR, PipelineExecutableStatisticKHRAllocator>>::type Device::getPipelineExecutableStatisticsKHR( const VULKAN_HPP_NAMESPACE::PipelineExecutableInfoKHR & executableInfo, PipelineExecutableStatisticKHRAllocator & pipelineExecutableStatisticKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PipelineExecutableStatisticKHR, PipelineExecutableStatisticKHRAllocator> statistics( pipelineExecutableStatisticKHRAllocator );
    uint32_t statisticCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineExecutableStatisticsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &statisticCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && statisticCount )
      {
        statistics.resize( statisticCount );
        result = static_cast<Result>( d.vkGetPipelineExecutableStatisticsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &statisticCount, reinterpret_cast<VkPipelineExecutableStatisticKHR *>( statistics.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( statisticCount <= statistics.size() );
      if ( statisticCount < statistics.size() )
      {
        statistics.resize( statisticCount );
      }
    }
    return createResultValue( result, statistics, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineExecutableStatisticsKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getPipelineExecutableInternalRepresentationsKHR( const VULKAN_HPP_NAMESPACE::PipelineExecutableInfoKHR * pExecutableInfo, uint32_t * pInternalRepresentationCount, VULKAN_HPP_NAMESPACE::PipelineExecutableInternalRepresentationKHR * pInternalRepresentations, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetPipelineExecutableInternalRepresentationsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( pExecutableInfo ), pInternalRepresentationCount, reinterpret_cast<VkPipelineExecutableInternalRepresentationKHR *>( pInternalRepresentations ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineExecutableInternalRepresentationKHRAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PipelineExecutableInternalRepresentationKHR, PipelineExecutableInternalRepresentationKHRAllocator>>::type Device::getPipelineExecutableInternalRepresentationsKHR( const VULKAN_HPP_NAMESPACE::PipelineExecutableInfoKHR & executableInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PipelineExecutableInternalRepresentationKHR, PipelineExecutableInternalRepresentationKHRAllocator> internalRepresentations;
    uint32_t internalRepresentationCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineExecutableInternalRepresentationsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &internalRepresentationCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && internalRepresentationCount )
      {
        internalRepresentations.resize( internalRepresentationCount );
        result = static_cast<Result>( d.vkGetPipelineExecutableInternalRepresentationsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &internalRepresentationCount, reinterpret_cast<VkPipelineExecutableInternalRepresentationKHR *>( internalRepresentations.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( internalRepresentationCount <= internalRepresentations.size() );
      if ( internalRepresentationCount < internalRepresentations.size() )
      {
        internalRepresentations.resize( internalRepresentationCount );
      }
    }
    return createResultValue( result, internalRepresentations, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineExecutableInternalRepresentationsKHR" );
  }

  template <typename PipelineExecutableInternalRepresentationKHRAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, PipelineExecutableInternalRepresentationKHR>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE typename ResultValueType<std::vector<PipelineExecutableInternalRepresentationKHR, PipelineExecutableInternalRepresentationKHRAllocator>>::type Device::getPipelineExecutableInternalRepresentationsKHR( const VULKAN_HPP_NAMESPACE::PipelineExecutableInfoKHR & executableInfo, PipelineExecutableInternalRepresentationKHRAllocator & pipelineExecutableInternalRepresentationKHRAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<PipelineExecutableInternalRepresentationKHR, PipelineExecutableInternalRepresentationKHRAllocator> internalRepresentations( pipelineExecutableInternalRepresentationKHRAllocator );
    uint32_t internalRepresentationCount;
    Result result;
    do
    {
      result = static_cast<Result>( d.vkGetPipelineExecutableInternalRepresentationsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &internalRepresentationCount, nullptr ) );
      if ( ( result == Result::eSuccess ) && internalRepresentationCount )
      {
        internalRepresentations.resize( internalRepresentationCount );
        result = static_cast<Result>( d.vkGetPipelineExecutableInternalRepresentationsKHR( m_device, reinterpret_cast<const VkPipelineExecutableInfoKHR *>( &executableInfo ), &internalRepresentationCount, reinterpret_cast<VkPipelineExecutableInternalRepresentationKHR *>( internalRepresentations.data() ) ) );
      }
    } while ( result == Result::eIncomplete );
    if ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )
    {
      VULKAN_HPP_ASSERT( internalRepresentationCount <= internalRepresentations.size() );
      if ( internalRepresentationCount < internalRepresentations.size() )
      {
        internalRepresentations.resize( internalRepresentationCount );
      }
    }
    return createResultValue( result, internalRepresentations, VULKAN_HPP_NAMESPACE_STRING"::Device::getPipelineExecutableInternalRepresentationsKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_device_generated_commands ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getGeneratedCommandsMemoryRequirementsNV( const VULKAN_HPP_NAMESPACE::GeneratedCommandsMemoryRequirementsInfoNV * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetGeneratedCommandsMemoryRequirementsNV( m_device, reinterpret_cast<const VkGeneratedCommandsMemoryRequirementsInfoNV *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getGeneratedCommandsMemoryRequirementsNV( const VULKAN_HPP_NAMESPACE::GeneratedCommandsMemoryRequirementsInfoNV & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetGeneratedCommandsMemoryRequirementsNV( m_device, reinterpret_cast<const VkGeneratedCommandsMemoryRequirementsInfoNV *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getGeneratedCommandsMemoryRequirementsNV( const VULKAN_HPP_NAMESPACE::GeneratedCommandsMemoryRequirementsInfoNV & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetGeneratedCommandsMemoryRequirementsNV( m_device, reinterpret_cast<const VkGeneratedCommandsMemoryRequirementsInfoNV *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::preprocessGeneratedCommandsNV( const VULKAN_HPP_NAMESPACE::GeneratedCommandsInfoNV * pGeneratedCommandsInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPreprocessGeneratedCommandsNV( m_commandBuffer, reinterpret_cast<const VkGeneratedCommandsInfoNV *>( pGeneratedCommandsInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::preprocessGeneratedCommandsNV( const VULKAN_HPP_NAMESPACE::GeneratedCommandsInfoNV & generatedCommandsInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPreprocessGeneratedCommandsNV( m_commandBuffer, reinterpret_cast<const VkGeneratedCommandsInfoNV *>( &generatedCommandsInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::executeGeneratedCommandsNV( VULKAN_HPP_NAMESPACE::Bool32 isPreprocessed, const VULKAN_HPP_NAMESPACE::GeneratedCommandsInfoNV * pGeneratedCommandsInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdExecuteGeneratedCommandsNV( m_commandBuffer, static_cast<VkBool32>( isPreprocessed ), reinterpret_cast<const VkGeneratedCommandsInfoNV *>( pGeneratedCommandsInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::executeGeneratedCommandsNV( VULKAN_HPP_NAMESPACE::Bool32 isPreprocessed, const VULKAN_HPP_NAMESPACE::GeneratedCommandsInfoNV & generatedCommandsInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdExecuteGeneratedCommandsNV( m_commandBuffer, static_cast<VkBool32>( isPreprocessed ), reinterpret_cast<const VkGeneratedCommandsInfoNV *>( &generatedCommandsInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindPipelineShaderGroupNV( VULKAN_HPP_NAMESPACE::PipelineBindPoint pipelineBindPoint, VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t groupIndex, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindPipelineShaderGroupNV( m_commandBuffer, static_cast<VkPipelineBindPoint>( pipelineBindPoint ), static_cast<VkPipeline>( pipeline ), groupIndex );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createIndirectCommandsLayoutNV( const VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutCreateInfoNV * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV * pIndirectCommandsLayout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateIndirectCommandsLayoutNV( m_device, reinterpret_cast<const VkIndirectCommandsLayoutCreateInfoNV *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkIndirectCommandsLayoutNV *>( pIndirectCommandsLayout ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV >::type Device::createIndirectCommandsLayoutNV( const VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutCreateInfoNV & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV  indirectCommandsLayout;
    Result result = static_cast<Result>( d.vkCreateIndirectCommandsLayoutNV( m_device, reinterpret_cast<const VkIndirectCommandsLayoutCreateInfoNV *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkIndirectCommandsLayoutNV *>( &indirectCommandsLayout ) ) );
    return createResultValue( result, indirectCommandsLayout, VULKAN_HPP_NAMESPACE_STRING "::Device::createIndirectCommandsLayoutNV" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV, Dispatch>>::type Device::createIndirectCommandsLayoutNVUnique( const VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutCreateInfoNV & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV indirectCommandsLayout;
    Result result = static_cast<Result>( d.vkCreateIndirectCommandsLayoutNV( m_device, reinterpret_cast<const VkIndirectCommandsLayoutCreateInfoNV *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkIndirectCommandsLayoutNV *>( &indirectCommandsLayout ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV, Dispatch>( result, indirectCommandsLayout, VULKAN_HPP_NAMESPACE_STRING "::Device::createIndirectCommandsLayoutNVUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyIndirectCommandsLayoutNV( VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV indirectCommandsLayout, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyIndirectCommandsLayoutNV( m_device, static_cast<VkIndirectCommandsLayoutNV>( indirectCommandsLayout ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyIndirectCommandsLayoutNV( VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV indirectCommandsLayout, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyIndirectCommandsLayoutNV( m_device, static_cast<VkIndirectCommandsLayoutNV>( indirectCommandsLayout ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV indirectCommandsLayout, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyIndirectCommandsLayoutNV( m_device, static_cast<VkIndirectCommandsLayoutNV>( indirectCommandsLayout ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::IndirectCommandsLayoutNV indirectCommandsLayout, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyIndirectCommandsLayoutNV( m_device, static_cast<VkIndirectCommandsLayoutNV>( indirectCommandsLayout ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_acquire_drm_display ===


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::acquireDrmDisplayEXT( int32_t drmFd, VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireDrmDisplayEXT( m_physicalDevice, drmFd, static_cast<VkDisplayKHR>( display ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type PhysicalDevice::acquireDrmDisplayEXT( int32_t drmFd, VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkAcquireDrmDisplayEXT( m_physicalDevice, drmFd, static_cast<VkDisplayKHR>( display ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::acquireDrmDisplayEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getDrmDisplayEXT( int32_t drmFd, uint32_t connectorId, VULKAN_HPP_NAMESPACE::DisplayKHR * display, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDrmDisplayEXT( m_physicalDevice, drmFd, connectorId, reinterpret_cast<VkDisplayKHR *>( display ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DisplayKHR >::type PhysicalDevice::getDrmDisplayEXT( int32_t drmFd, uint32_t connectorId, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DisplayKHR  display;
    Result result = static_cast<Result>( d.vkGetDrmDisplayEXT( m_physicalDevice, drmFd, connectorId, reinterpret_cast<VkDisplayKHR *>( &display ) ) );
    return createResultValue( result, display, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getDrmDisplayEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DisplayKHR, Dispatch>>::type PhysicalDevice::getDrmDisplayEXTUnique( int32_t drmFd, uint32_t connectorId, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DisplayKHR display;
    Result result = static_cast<Result>( d.vkGetDrmDisplayEXT( m_physicalDevice, drmFd, connectorId, reinterpret_cast<VkDisplayKHR *>( &display ) ) );
    ObjectRelease<PhysicalDevice, Dispatch> deleter( *this, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DisplayKHR, Dispatch>( result, display, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getDrmDisplayEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_private_data ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createPrivateDataSlotEXT( const VULKAN_HPP_NAMESPACE::PrivateDataSlotCreateInfo * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::PrivateDataSlot * pPrivateDataSlot, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreatePrivateDataSlotEXT( m_device, reinterpret_cast<const VkPrivateDataSlotCreateInfo *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPrivateDataSlot *>( pPrivateDataSlot ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::PrivateDataSlot >::type Device::createPrivateDataSlotEXT( const VULKAN_HPP_NAMESPACE::PrivateDataSlotCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::PrivateDataSlot  privateDataSlot;
    Result result = static_cast<Result>( d.vkCreatePrivateDataSlotEXT( m_device, reinterpret_cast<const VkPrivateDataSlotCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPrivateDataSlot *>( &privateDataSlot ) ) );
    return createResultValue( result, privateDataSlot, VULKAN_HPP_NAMESPACE_STRING "::Device::createPrivateDataSlotEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::PrivateDataSlot, Dispatch>>::type Device::createPrivateDataSlotEXTUnique( const VULKAN_HPP_NAMESPACE::PrivateDataSlotCreateInfo & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot;
    Result result = static_cast<Result>( d.vkCreatePrivateDataSlotEXT( m_device, reinterpret_cast<const VkPrivateDataSlotCreateInfo *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPrivateDataSlot *>( &privateDataSlot ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::PrivateDataSlot, Dispatch>( result, privateDataSlot, VULKAN_HPP_NAMESPACE_STRING "::Device::createPrivateDataSlotEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPrivateDataSlotEXT( VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyPrivateDataSlotEXT( m_device, static_cast<VkPrivateDataSlot>( privateDataSlot ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyPrivateDataSlotEXT( VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyPrivateDataSlotEXT( m_device, static_cast<VkPrivateDataSlot>( privateDataSlot ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setPrivateDataEXT( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, uint64_t data, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetPrivateDataEXT( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), data ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setPrivateDataEXT( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, uint64_t data, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetPrivateDataEXT( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), data ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setPrivateDataEXT" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getPrivateDataEXT( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, uint64_t * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetPrivateDataEXT( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), pData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE uint64_t  Device::getPrivateDataEXT( VULKAN_HPP_NAMESPACE::ObjectType objectType, uint64_t objectHandle, VULKAN_HPP_NAMESPACE::PrivateDataSlot privateDataSlot, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    uint64_t  data;
    d.vkGetPrivateDataEXT( m_device, static_cast<VkObjectType>( objectType ), objectHandle, static_cast<VkPrivateDataSlot>( privateDataSlot ), &data );
    return data;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_KHR_video_encode_queue ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::encodeVideoKHR( const VULKAN_HPP_NAMESPACE::VideoEncodeInfoKHR * pEncodeInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdEncodeVideoKHR( m_commandBuffer, reinterpret_cast<const VkVideoEncodeInfoKHR *>( pEncodeInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::encodeVideoKHR( const VULKAN_HPP_NAMESPACE::VideoEncodeInfoKHR & encodeInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdEncodeVideoKHR( m_commandBuffer, reinterpret_cast<const VkVideoEncodeInfoKHR *>( &encodeInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_KHR_synchronization2 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setEvent2KHR( VULKAN_HPP_NAMESPACE::Event event, const VULKAN_HPP_NAMESPACE::DependencyInfo * pDependencyInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetEvent2KHR( m_commandBuffer, static_cast<VkEvent>( event ), reinterpret_cast<const VkDependencyInfo *>( pDependencyInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setEvent2KHR( VULKAN_HPP_NAMESPACE::Event event, const VULKAN_HPP_NAMESPACE::DependencyInfo & dependencyInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetEvent2KHR( m_commandBuffer, static_cast<VkEvent>( event ), reinterpret_cast<const VkDependencyInfo *>( &dependencyInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resetEvent2KHR( VULKAN_HPP_NAMESPACE::Event event, VULKAN_HPP_NAMESPACE::PipelineStageFlags2 stageMask, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResetEvent2KHR( m_commandBuffer, static_cast<VkEvent>( event ), static_cast<VkPipelineStageFlags2>( stageMask ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::waitEvents2KHR( uint32_t eventCount, const VULKAN_HPP_NAMESPACE::Event * pEvents, const VULKAN_HPP_NAMESPACE::DependencyInfo * pDependencyInfos, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWaitEvents2KHR( m_commandBuffer, eventCount, reinterpret_cast<const VkEvent *>( pEvents ), reinterpret_cast<const VkDependencyInfo *>( pDependencyInfos ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::waitEvents2KHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::Event> const & events, ArrayProxy<const VULKAN_HPP_NAMESPACE::DependencyInfo> const & dependencyInfos, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT_WHEN_NO_EXCEPTIONS
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
#ifdef VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT( events.size() == dependencyInfos.size() );
#else
    if ( events.size() != dependencyInfos.size() )
  {
    throw LogicError( VULKAN_HPP_NAMESPACE_STRING "::CommandBuffer::waitEvents2KHR: events.size() != dependencyInfos.size()" );
  }
#endif  /*VULKAN_HPP_NO_EXCEPTIONS*/
    
    d.vkCmdWaitEvents2KHR( m_commandBuffer, events.size(), reinterpret_cast<const VkEvent *>( events.data() ), reinterpret_cast<const VkDependencyInfo *>( dependencyInfos.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pipelineBarrier2KHR( const VULKAN_HPP_NAMESPACE::DependencyInfo * pDependencyInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdPipelineBarrier2KHR( m_commandBuffer, reinterpret_cast<const VkDependencyInfo *>( pDependencyInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::pipelineBarrier2KHR( const VULKAN_HPP_NAMESPACE::DependencyInfo & dependencyInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdPipelineBarrier2KHR( m_commandBuffer, reinterpret_cast<const VkDependencyInfo *>( &dependencyInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeTimestamp2KHR( VULKAN_HPP_NAMESPACE::PipelineStageFlags2 stage, VULKAN_HPP_NAMESPACE::QueryPool queryPool, uint32_t query, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteTimestamp2KHR( m_commandBuffer, static_cast<VkPipelineStageFlags2>( stage ), static_cast<VkQueryPool>( queryPool ), query );
  }


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Queue::submit2KHR( uint32_t submitCount, const VULKAN_HPP_NAMESPACE::SubmitInfo2 * pSubmits, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkQueueSubmit2KHR( m_queue, submitCount, reinterpret_cast<const VkSubmitInfo2 *>( pSubmits ), static_cast<VkFence>( fence ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Queue::submit2KHR( ArrayProxy<const VULKAN_HPP_NAMESPACE::SubmitInfo2> const & submits, VULKAN_HPP_NAMESPACE::Fence fence, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkQueueSubmit2KHR( m_queue, submits.size(), reinterpret_cast<const VkSubmitInfo2 *>( submits.data() ), static_cast<VkFence>( fence ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Queue::submit2KHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::writeBufferMarker2AMD( VULKAN_HPP_NAMESPACE::PipelineStageFlags2 stage, VULKAN_HPP_NAMESPACE::Buffer dstBuffer, VULKAN_HPP_NAMESPACE::DeviceSize dstOffset, uint32_t marker, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdWriteBufferMarker2AMD( m_commandBuffer, static_cast<VkPipelineStageFlags2>( stage ), static_cast<VkBuffer>( dstBuffer ), static_cast<VkDeviceSize>( dstOffset ), marker );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Queue::getCheckpointData2NV( uint32_t * pCheckpointDataCount, VULKAN_HPP_NAMESPACE::CheckpointData2NV * pCheckpointData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetQueueCheckpointData2NV( m_queue, pCheckpointDataCount, reinterpret_cast<VkCheckpointData2NV *>( pCheckpointData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename CheckpointData2NVAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<CheckpointData2NV, CheckpointData2NVAllocator> Queue::getCheckpointData2NV( Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<CheckpointData2NV, CheckpointData2NVAllocator> checkpointData;
    uint32_t checkpointDataCount;
    d.vkGetQueueCheckpointData2NV( m_queue, &checkpointDataCount, nullptr );
    checkpointData.resize( checkpointDataCount );
    d.vkGetQueueCheckpointData2NV( m_queue, &checkpointDataCount, reinterpret_cast<VkCheckpointData2NV *>( checkpointData.data() ) );
    VULKAN_HPP_ASSERT( checkpointDataCount <= checkpointData.size() );
    return checkpointData;
  }

  template <typename CheckpointData2NVAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, CheckpointData2NV>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<CheckpointData2NV, CheckpointData2NVAllocator> Queue::getCheckpointData2NV( CheckpointData2NVAllocator & checkpointData2NVAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<CheckpointData2NV, CheckpointData2NVAllocator> checkpointData( checkpointData2NVAllocator );
    uint32_t checkpointDataCount;
    d.vkGetQueueCheckpointData2NV( m_queue, &checkpointDataCount, nullptr );
    checkpointData.resize( checkpointDataCount );
    d.vkGetQueueCheckpointData2NV( m_queue, &checkpointDataCount, reinterpret_cast<VkCheckpointData2NV *>( checkpointData.data() ) );
    VULKAN_HPP_ASSERT( checkpointDataCount <= checkpointData.size() );
    return checkpointData;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_NV_fragment_shading_rate_enums ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setFragmentShadingRateEnumNV( VULKAN_HPP_NAMESPACE::FragmentShadingRateNV shadingRate, const VULKAN_HPP_NAMESPACE::FragmentShadingRateCombinerOpKHR combinerOps[2], Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetFragmentShadingRateEnumNV( m_commandBuffer, static_cast<VkFragmentShadingRateNV>( shadingRate ), reinterpret_cast<const VkFragmentShadingRateCombinerOpKHR *>( combinerOps ) );
  }

  //=== VK_KHR_copy_commands2 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBuffer2KHR( const VULKAN_HPP_NAMESPACE::CopyBufferInfo2 * pCopyBufferInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyBuffer2KHR( m_commandBuffer, reinterpret_cast<const VkCopyBufferInfo2 *>( pCopyBufferInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBuffer2KHR( const VULKAN_HPP_NAMESPACE::CopyBufferInfo2 & copyBufferInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyBuffer2KHR( m_commandBuffer, reinterpret_cast<const VkCopyBufferInfo2 *>( &copyBufferInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImage2KHR( const VULKAN_HPP_NAMESPACE::CopyImageInfo2 * pCopyImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyImage2KHR( m_commandBuffer, reinterpret_cast<const VkCopyImageInfo2 *>( pCopyImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImage2KHR( const VULKAN_HPP_NAMESPACE::CopyImageInfo2 & copyImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyImage2KHR( m_commandBuffer, reinterpret_cast<const VkCopyImageInfo2 *>( &copyImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBufferToImage2KHR( const VULKAN_HPP_NAMESPACE::CopyBufferToImageInfo2 * pCopyBufferToImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyBufferToImage2KHR( m_commandBuffer, reinterpret_cast<const VkCopyBufferToImageInfo2 *>( pCopyBufferToImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyBufferToImage2KHR( const VULKAN_HPP_NAMESPACE::CopyBufferToImageInfo2 & copyBufferToImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyBufferToImage2KHR( m_commandBuffer, reinterpret_cast<const VkCopyBufferToImageInfo2 *>( &copyBufferToImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImageToBuffer2KHR( const VULKAN_HPP_NAMESPACE::CopyImageToBufferInfo2 * pCopyImageToBufferInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdCopyImageToBuffer2KHR( m_commandBuffer, reinterpret_cast<const VkCopyImageToBufferInfo2 *>( pCopyImageToBufferInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::copyImageToBuffer2KHR( const VULKAN_HPP_NAMESPACE::CopyImageToBufferInfo2 & copyImageToBufferInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdCopyImageToBuffer2KHR( m_commandBuffer, reinterpret_cast<const VkCopyImageToBufferInfo2 *>( &copyImageToBufferInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::blitImage2KHR( const VULKAN_HPP_NAMESPACE::BlitImageInfo2 * pBlitImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBlitImage2KHR( m_commandBuffer, reinterpret_cast<const VkBlitImageInfo2 *>( pBlitImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::blitImage2KHR( const VULKAN_HPP_NAMESPACE::BlitImageInfo2 & blitImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdBlitImage2KHR( m_commandBuffer, reinterpret_cast<const VkBlitImageInfo2 *>( &blitImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resolveImage2KHR( const VULKAN_HPP_NAMESPACE::ResolveImageInfo2 * pResolveImageInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdResolveImage2KHR( m_commandBuffer, reinterpret_cast<const VkResolveImageInfo2 *>( pResolveImageInfo ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::resolveImage2KHR( const VULKAN_HPP_NAMESPACE::ResolveImageInfo2 & resolveImageInfo, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdResolveImage2KHR( m_commandBuffer, reinterpret_cast<const VkResolveImageInfo2 *>( &resolveImageInfo ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_acquire_winrt_display ===


#ifdef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::acquireWinrtDisplayNV( VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkAcquireWinrtDisplayNV( m_physicalDevice, static_cast<VkDisplayKHR>( display ) ) );
  }
#else
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type PhysicalDevice::acquireWinrtDisplayNV( VULKAN_HPP_NAMESPACE::DisplayKHR display, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkAcquireWinrtDisplayNV( m_physicalDevice, static_cast<VkDisplayKHR>( display ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::acquireWinrtDisplayNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result PhysicalDevice::getWinrtDisplayNV( uint32_t deviceRelativeId, VULKAN_HPP_NAMESPACE::DisplayKHR * pDisplay, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetWinrtDisplayNV( m_physicalDevice, deviceRelativeId, reinterpret_cast<VkDisplayKHR *>( pDisplay ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::DisplayKHR >::type PhysicalDevice::getWinrtDisplayNV( uint32_t deviceRelativeId, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DisplayKHR  display;
    Result result = static_cast<Result>( d.vkGetWinrtDisplayNV( m_physicalDevice, deviceRelativeId, reinterpret_cast<VkDisplayKHR *>( &display ) ) );
    return createResultValue( result, display, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getWinrtDisplayNV" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::DisplayKHR, Dispatch>>::type PhysicalDevice::getWinrtDisplayNVUnique( uint32_t deviceRelativeId, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::DisplayKHR display;
    Result result = static_cast<Result>( d.vkGetWinrtDisplayNV( m_physicalDevice, deviceRelativeId, reinterpret_cast<VkDisplayKHR *>( &display ) ) );
    ObjectRelease<PhysicalDevice, Dispatch> deleter( *this, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::DisplayKHR, Dispatch>( result, display, VULKAN_HPP_NAMESPACE_STRING "::PhysicalDevice::getWinrtDisplayNVUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

#if defined( VK_USE_PLATFORM_DIRECTFB_EXT )
  //=== VK_EXT_directfb_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createDirectFBSurfaceEXT( const VULKAN_HPP_NAMESPACE::DirectFBSurfaceCreateInfoEXT * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateDirectFBSurfaceEXT( m_instance, reinterpret_cast<const VkDirectFBSurfaceCreateInfoEXT *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createDirectFBSurfaceEXT( const VULKAN_HPP_NAMESPACE::DirectFBSurfaceCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateDirectFBSurfaceEXT( m_instance, reinterpret_cast<const VkDirectFBSurfaceCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDirectFBSurfaceEXT" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createDirectFBSurfaceEXTUnique( const VULKAN_HPP_NAMESPACE::DirectFBSurfaceCreateInfoEXT & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateDirectFBSurfaceEXT( m_instance, reinterpret_cast<const VkDirectFBSurfaceCreateInfoEXT *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createDirectFBSurfaceEXTUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getDirectFBPresentationSupportEXT( uint32_t queueFamilyIndex, IDirectFB * dfb, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Bool32>( d.vkGetPhysicalDeviceDirectFBPresentationSupportEXT( m_physicalDevice, queueFamilyIndex, dfb ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getDirectFBPresentationSupportEXT( uint32_t queueFamilyIndex, IDirectFB & dfb, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetPhysicalDeviceDirectFBPresentationSupportEXT( m_physicalDevice, queueFamilyIndex, &dfb );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_DIRECTFB_EXT*/

  //=== VK_KHR_ray_tracing_pipeline ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::traceRaysKHR( const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pRaygenShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pMissShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pHitShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdTraceRaysKHR( m_commandBuffer, reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pRaygenShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pMissShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pHitShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pCallableShaderBindingTable ), width, height, depth );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::traceRaysKHR( const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & raygenShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & missShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & hitShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & callableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdTraceRaysKHR( m_commandBuffer, reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &raygenShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &missShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &hitShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &callableShaderBindingTable ), width, height, depth );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createRayTracingPipelinesKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, uint32_t createInfoCount, const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR * pCreateInfos, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::Pipeline * pPipelines, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), createInfoCount, reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( pCreateInfos ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkPipeline *>( pPipelines ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename PipelineAllocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createRayTracingPipelinesKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename PipelineAllocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, Pipeline>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator>> Device::createRayTracingPipelinesKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<VULKAN_HPP_NAMESPACE::Pipeline, PipelineAllocator> pipelines( createInfos.size(), pipelineAllocator );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    return createResultValue( result, pipelines, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<VULKAN_HPP_NAMESPACE::Pipeline > Device::createRayTracingPipelineKHR( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Pipeline  pipeline;
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    return createResultValue( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelineKHR", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch, typename PipelineAllocator>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createRayTracingPipelinesKHRUnique( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines;
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR )|| ( result == VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesKHRUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch, typename PipelineAllocator, typename B, typename std::enable_if<std::is_same<typename B::value_type, UniqueHandle<Pipeline, Dispatch>>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator>> Device::createRayTracingPipelinesKHRUnique( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, ArrayProxy<const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR> const & createInfos, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, PipelineAllocator & pipelineAllocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<UniqueHandle<Pipeline, Dispatch>, PipelineAllocator> uniquePipelines( pipelineAllocator );
    std::vector<Pipeline> pipelines( createInfos.size() );
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), createInfos.size(), reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( createInfos.data() ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( pipelines.data() ) ) );
    if ( ( result == VULKAN_HPP_NAMESPACE::Result::eSuccess )|| ( result == VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR )|| ( result == VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR )|| ( result == VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT ) )
    {
      uniquePipelines.reserve( createInfos.size() );
      ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
      for ( size_t i=0; i < createInfos.size(); i++ )
      {
        uniquePipelines.push_back( UniqueHandle<Pipeline, Dispatch>( pipelines[i], deleter ) );
      }
    }
    return createResultValue( result, std::move( uniquePipelines ), VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelinesKHRUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT } );
  }

  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<UniqueHandle<Pipeline, Dispatch>> Device::createRayTracingPipelineKHRUnique( VULKAN_HPP_NAMESPACE::DeferredOperationKHR deferredOperation, VULKAN_HPP_NAMESPACE::PipelineCache pipelineCache, const VULKAN_HPP_NAMESPACE::RayTracingPipelineCreateInfoKHR & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    Pipeline pipeline;
    Result result = static_cast<Result>( d.vkCreateRayTracingPipelinesKHR( m_device, static_cast<VkDeferredOperationKHR>( deferredOperation ), static_cast<VkPipelineCache>( pipelineCache ), 1, reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkPipeline *>( &pipeline ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<Pipeline, Dispatch>( result, pipeline, VULKAN_HPP_NAMESPACE_STRING "::Device::createRayTracingPipelineKHRUnique", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eOperationDeferredKHR, VULKAN_HPP_NAMESPACE::Result::eOperationNotDeferredKHR, VULKAN_HPP_NAMESPACE::Result::ePipelineCompileRequiredEXT }, deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getRayTracingShaderGroupHandlesKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetRayTracingShaderGroupHandlesKHR( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, dataSize, pData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<DataType,Allocator>>::type Device::getRayTracingShaderGroupHandlesKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_ASSERT( dataSize % sizeof( DataType ) == 0 );
    std::vector<DataType,Allocator> data( dataSize / sizeof( DataType ) );
    Result result = static_cast<Result>( d.vkGetRayTracingShaderGroupHandlesKHR( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, data.size() * sizeof( DataType ), reinterpret_cast<void *>( data.data() ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getRayTracingShaderGroupHandlesKHR" );
  }

  template <typename DataType, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<DataType>::type Device::getRayTracingShaderGroupHandleKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    DataType data;
    Result result = static_cast<Result>( d.vkGetRayTracingShaderGroupHandlesKHR( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, sizeof( DataType ), reinterpret_cast<void *>( &data ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getRayTracingShaderGroupHandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getRayTracingCaptureReplayShaderGroupHandlesKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void * pData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetRayTracingCaptureReplayShaderGroupHandlesKHR( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, dataSize, pData ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename DataType, typename Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<std::vector<DataType,Allocator>>::type Device::getRayTracingCaptureReplayShaderGroupHandlesKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_ASSERT( dataSize % sizeof( DataType ) == 0 );
    std::vector<DataType,Allocator> data( dataSize / sizeof( DataType ) );
    Result result = static_cast<Result>( d.vkGetRayTracingCaptureReplayShaderGroupHandlesKHR( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, data.size() * sizeof( DataType ), reinterpret_cast<void *>( data.data() ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getRayTracingCaptureReplayShaderGroupHandlesKHR" );
  }

  template <typename DataType, typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<DataType>::type Device::getRayTracingCaptureReplayShaderGroupHandleKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    DataType data;
    Result result = static_cast<Result>( d.vkGetRayTracingCaptureReplayShaderGroupHandlesKHR( m_device, static_cast<VkPipeline>( pipeline ), firstGroup, groupCount, sizeof( DataType ), reinterpret_cast<void *>( &data ) ) );
    return createResultValue( result, data, VULKAN_HPP_NAMESPACE_STRING "::Device::getRayTracingCaptureReplayShaderGroupHandleKHR" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::traceRaysIndirectKHR( const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pRaygenShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pMissShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pHitShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR * pCallableShaderBindingTable, VULKAN_HPP_NAMESPACE::DeviceAddress indirectDeviceAddress, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdTraceRaysIndirectKHR( m_commandBuffer, reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pRaygenShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pMissShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pHitShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( pCallableShaderBindingTable ), static_cast<VkDeviceAddress>( indirectDeviceAddress ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::traceRaysIndirectKHR( const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & raygenShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & missShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & hitShaderBindingTable, const VULKAN_HPP_NAMESPACE::StridedDeviceAddressRegionKHR & callableShaderBindingTable, VULKAN_HPP_NAMESPACE::DeviceAddress indirectDeviceAddress, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdTraceRaysIndirectKHR( m_commandBuffer, reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &raygenShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &missShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &hitShaderBindingTable ), reinterpret_cast<const VkStridedDeviceAddressRegionKHR *>( &callableShaderBindingTable ), static_cast<VkDeviceAddress>( indirectDeviceAddress ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE DeviceSize Device::getRayTracingShaderGroupStackSizeKHR( VULKAN_HPP_NAMESPACE::Pipeline pipeline, uint32_t group, VULKAN_HPP_NAMESPACE::ShaderGroupShaderKHR groupShader, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<DeviceSize>( d.vkGetRayTracingShaderGroupStackSizeKHR( m_device, static_cast<VkPipeline>( pipeline ), group, static_cast<VkShaderGroupShaderKHR>( groupShader ) ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setRayTracingPipelineStackSizeKHR( uint32_t pipelineStackSize, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetRayTracingPipelineStackSizeKHR( m_commandBuffer, pipelineStackSize );
  }

  //=== VK_EXT_vertex_input_dynamic_state ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setVertexInputEXT( uint32_t vertexBindingDescriptionCount, const VULKAN_HPP_NAMESPACE::VertexInputBindingDescription2EXT * pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VULKAN_HPP_NAMESPACE::VertexInputAttributeDescription2EXT * pVertexAttributeDescriptions, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetVertexInputEXT( m_commandBuffer, vertexBindingDescriptionCount, reinterpret_cast<const VkVertexInputBindingDescription2EXT *>( pVertexBindingDescriptions ), vertexAttributeDescriptionCount, reinterpret_cast<const VkVertexInputAttributeDescription2EXT *>( pVertexAttributeDescriptions ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setVertexInputEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::VertexInputBindingDescription2EXT> const & vertexBindingDescriptions, ArrayProxy<const VULKAN_HPP_NAMESPACE::VertexInputAttributeDescription2EXT> const & vertexAttributeDescriptions, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetVertexInputEXT( m_commandBuffer, vertexBindingDescriptions.size(), reinterpret_cast<const VkVertexInputBindingDescription2EXT *>( vertexBindingDescriptions.data() ), vertexAttributeDescriptions.size(), reinterpret_cast<const VkVertexInputAttributeDescription2EXT *>( vertexAttributeDescriptions.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_external_memory ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryZirconHandleFUCHSIA( const VULKAN_HPP_NAMESPACE::MemoryGetZirconHandleInfoFUCHSIA * pGetZirconHandleInfo, zx_handle_t * pZirconHandle, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryZirconHandleFUCHSIA( m_device, reinterpret_cast<const VkMemoryGetZirconHandleInfoFUCHSIA *>( pGetZirconHandleInfo ), pZirconHandle ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<zx_handle_t >::type Device::getMemoryZirconHandleFUCHSIA( const VULKAN_HPP_NAMESPACE::MemoryGetZirconHandleInfoFUCHSIA & getZirconHandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    zx_handle_t  zirconHandle;
    Result result = static_cast<Result>( d.vkGetMemoryZirconHandleFUCHSIA( m_device, reinterpret_cast<const VkMemoryGetZirconHandleInfoFUCHSIA *>( &getZirconHandleInfo ), &zirconHandle ) );
    return createResultValue( result, zirconHandle, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryZirconHandleFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryZirconHandlePropertiesFUCHSIA( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VULKAN_HPP_NAMESPACE::MemoryZirconHandlePropertiesFUCHSIA * pMemoryZirconHandleProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryZirconHandlePropertiesFUCHSIA( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), zirconHandle, reinterpret_cast<VkMemoryZirconHandlePropertiesFUCHSIA *>( pMemoryZirconHandleProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::MemoryZirconHandlePropertiesFUCHSIA >::type Device::getMemoryZirconHandlePropertiesFUCHSIA( VULKAN_HPP_NAMESPACE::ExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryZirconHandlePropertiesFUCHSIA  memoryZirconHandleProperties;
    Result result = static_cast<Result>( d.vkGetMemoryZirconHandlePropertiesFUCHSIA( m_device, static_cast<VkExternalMemoryHandleTypeFlagBits>( handleType ), zirconHandle, reinterpret_cast<VkMemoryZirconHandlePropertiesFUCHSIA *>( &memoryZirconHandleProperties ) ) );
    return createResultValue( result, memoryZirconHandleProperties, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryZirconHandlePropertiesFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_external_semaphore ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::importSemaphoreZirconHandleFUCHSIA( const VULKAN_HPP_NAMESPACE::ImportSemaphoreZirconHandleInfoFUCHSIA * pImportSemaphoreZirconHandleInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkImportSemaphoreZirconHandleFUCHSIA( m_device, reinterpret_cast<const VkImportSemaphoreZirconHandleInfoFUCHSIA *>( pImportSemaphoreZirconHandleInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::importSemaphoreZirconHandleFUCHSIA( const VULKAN_HPP_NAMESPACE::ImportSemaphoreZirconHandleInfoFUCHSIA & importSemaphoreZirconHandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkImportSemaphoreZirconHandleFUCHSIA( m_device, reinterpret_cast<const VkImportSemaphoreZirconHandleInfoFUCHSIA *>( &importSemaphoreZirconHandleInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::importSemaphoreZirconHandleFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSemaphoreZirconHandleFUCHSIA( const VULKAN_HPP_NAMESPACE::SemaphoreGetZirconHandleInfoFUCHSIA * pGetZirconHandleInfo, zx_handle_t * pZirconHandle, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetSemaphoreZirconHandleFUCHSIA( m_device, reinterpret_cast<const VkSemaphoreGetZirconHandleInfoFUCHSIA *>( pGetZirconHandleInfo ), pZirconHandle ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<zx_handle_t >::type Device::getSemaphoreZirconHandleFUCHSIA( const VULKAN_HPP_NAMESPACE::SemaphoreGetZirconHandleInfoFUCHSIA & getZirconHandleInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    zx_handle_t  zirconHandle;
    Result result = static_cast<Result>( d.vkGetSemaphoreZirconHandleFUCHSIA( m_device, reinterpret_cast<const VkSemaphoreGetZirconHandleInfoFUCHSIA *>( &getZirconHandleInfo ), &zirconHandle ) );
    return createResultValue( result, zirconHandle, VULKAN_HPP_NAMESPACE_STRING "::Device::getSemaphoreZirconHandleFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_buffer_collection ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::createBufferCollectionFUCHSIA( const VULKAN_HPP_NAMESPACE::BufferCollectionCreateInfoFUCHSIA * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA * pCollection, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateBufferCollectionFUCHSIA( m_device, reinterpret_cast<const VkBufferCollectionCreateInfoFUCHSIA *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkBufferCollectionFUCHSIA *>( pCollection ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA >::type Device::createBufferCollectionFUCHSIA( const VULKAN_HPP_NAMESPACE::BufferCollectionCreateInfoFUCHSIA & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA  collection;
    Result result = static_cast<Result>( d.vkCreateBufferCollectionFUCHSIA( m_device, reinterpret_cast<const VkBufferCollectionCreateInfoFUCHSIA *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkBufferCollectionFUCHSIA *>( &collection ) ) );
    return createResultValue( result, collection, VULKAN_HPP_NAMESPACE_STRING "::Device::createBufferCollectionFUCHSIA" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA, Dispatch>>::type Device::createBufferCollectionFUCHSIAUnique( const VULKAN_HPP_NAMESPACE::BufferCollectionCreateInfoFUCHSIA & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection;
    Result result = static_cast<Result>( d.vkCreateBufferCollectionFUCHSIA( m_device, reinterpret_cast<const VkBufferCollectionCreateInfoFUCHSIA *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkBufferCollectionFUCHSIA *>( &collection ) ) );
    ObjectDestroy<Device, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA, Dispatch>( result, collection, VULKAN_HPP_NAMESPACE_STRING "::Device::createBufferCollectionFUCHSIAUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setBufferCollectionImageConstraintsFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, const VULKAN_HPP_NAMESPACE::ImageConstraintsInfoFUCHSIA * pImageConstraintsInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetBufferCollectionImageConstraintsFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkImageConstraintsInfoFUCHSIA *>( pImageConstraintsInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setBufferCollectionImageConstraintsFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, const VULKAN_HPP_NAMESPACE::ImageConstraintsInfoFUCHSIA & imageConstraintsInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetBufferCollectionImageConstraintsFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkImageConstraintsInfoFUCHSIA *>( &imageConstraintsInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setBufferCollectionImageConstraintsFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::setBufferCollectionBufferConstraintsFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, const VULKAN_HPP_NAMESPACE::BufferConstraintsInfoFUCHSIA * pBufferConstraintsInfo, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkSetBufferCollectionBufferConstraintsFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkBufferConstraintsInfoFUCHSIA *>( pBufferConstraintsInfo ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<void>::type Device::setBufferCollectionBufferConstraintsFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, const VULKAN_HPP_NAMESPACE::BufferConstraintsInfoFUCHSIA & bufferConstraintsInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    Result result = static_cast<Result>( d.vkSetBufferCollectionBufferConstraintsFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkBufferConstraintsInfoFUCHSIA *>( &bufferConstraintsInfo ) ) );
    return createResultValue( result, VULKAN_HPP_NAMESPACE_STRING "::Device::setBufferCollectionBufferConstraintsFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyBufferCollectionFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyBufferCollectionFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroyBufferCollectionFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyBufferCollectionFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkDestroyBufferCollectionFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::destroy( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkDestroyBufferCollectionFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getBufferCollectionPropertiesFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, VULKAN_HPP_NAMESPACE::BufferCollectionPropertiesFUCHSIA * pProperties, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetBufferCollectionPropertiesFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<VkBufferCollectionPropertiesFUCHSIA *>( pProperties ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::BufferCollectionPropertiesFUCHSIA >::type Device::getBufferCollectionPropertiesFUCHSIA( VULKAN_HPP_NAMESPACE::BufferCollectionFUCHSIA collection, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::BufferCollectionPropertiesFUCHSIA  properties;
    Result result = static_cast<Result>( d.vkGetBufferCollectionPropertiesFUCHSIA( m_device, static_cast<VkBufferCollectionFUCHSIA>( collection ), reinterpret_cast<VkBufferCollectionPropertiesFUCHSIA *>( &properties ) ) );
    return createResultValue( result, properties, VULKAN_HPP_NAMESPACE_STRING "::Device::getBufferCollectionPropertiesFUCHSIA" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_FUCHSIA*/

  //=== VK_HUAWEI_subpass_shading ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getSubpassShadingMaxWorkgroupSizeHUAWEI( VULKAN_HPP_NAMESPACE::RenderPass renderpass, VULKAN_HPP_NAMESPACE::Extent2D * pMaxWorkgroupSize, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI( m_device, static_cast<VkRenderPass>( renderpass ), reinterpret_cast<VkExtent2D *>( pMaxWorkgroupSize ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE ResultValue<VULKAN_HPP_NAMESPACE::Extent2D > Device::getSubpassShadingMaxWorkgroupSizeHUAWEI( VULKAN_HPP_NAMESPACE::RenderPass renderpass, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::Extent2D  maxWorkgroupSize;
    Result result = static_cast<Result>( d.vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI( m_device, static_cast<VkRenderPass>( renderpass ), reinterpret_cast<VkExtent2D *>( &maxWorkgroupSize ) ) );
    return createResultValue( result, maxWorkgroupSize, VULKAN_HPP_NAMESPACE_STRING "::Device::getSubpassShadingMaxWorkgroupSizeHUAWEI", { VULKAN_HPP_NAMESPACE::Result::eSuccess, VULKAN_HPP_NAMESPACE::Result::eIncomplete } );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::subpassShadingHUAWEI( Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSubpassShadingHUAWEI( m_commandBuffer );
  }

  //=== VK_HUAWEI_invocation_mask ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::bindInvocationMaskHUAWEI( VULKAN_HPP_NAMESPACE::ImageView imageView, VULKAN_HPP_NAMESPACE::ImageLayout imageLayout, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdBindInvocationMaskHUAWEI( m_commandBuffer, static_cast<VkImageView>( imageView ), static_cast<VkImageLayout>( imageLayout ) );
  }

  //=== VK_NV_external_memory_rdma ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Device::getMemoryRemoteAddressNV( const VULKAN_HPP_NAMESPACE::MemoryGetRemoteAddressInfoNV * pMemoryGetRemoteAddressInfo, VULKAN_HPP_NAMESPACE::RemoteAddressNV * pAddress, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkGetMemoryRemoteAddressNV( m_device, reinterpret_cast<const VkMemoryGetRemoteAddressInfoNV *>( pMemoryGetRemoteAddressInfo ), reinterpret_cast<VkRemoteAddressNV *>( pAddress ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::RemoteAddressNV >::type Device::getMemoryRemoteAddressNV( const VULKAN_HPP_NAMESPACE::MemoryGetRemoteAddressInfoNV & memoryGetRemoteAddressInfo, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::RemoteAddressNV  address;
    Result result = static_cast<Result>( d.vkGetMemoryRemoteAddressNV( m_device, reinterpret_cast<const VkMemoryGetRemoteAddressInfoNV *>( &memoryGetRemoteAddressInfo ), reinterpret_cast<VkRemoteAddressNV *>( &address ) ) );
    return createResultValue( result, address, VULKAN_HPP_NAMESPACE_STRING "::Device::getMemoryRemoteAddressNV" );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_extended_dynamic_state2 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setPatchControlPointsEXT( uint32_t patchControlPoints, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetPatchControlPointsEXT( m_commandBuffer, patchControlPoints );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setRasterizerDiscardEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 rasterizerDiscardEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetRasterizerDiscardEnableEXT( m_commandBuffer, static_cast<VkBool32>( rasterizerDiscardEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setDepthBiasEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 depthBiasEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetDepthBiasEnableEXT( m_commandBuffer, static_cast<VkBool32>( depthBiasEnable ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setLogicOpEXT( VULKAN_HPP_NAMESPACE::LogicOp logicOp, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetLogicOpEXT( m_commandBuffer, static_cast<VkLogicOp>( logicOp ) );
  }


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setPrimitiveRestartEnableEXT( VULKAN_HPP_NAMESPACE::Bool32 primitiveRestartEnable, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetPrimitiveRestartEnableEXT( m_commandBuffer, static_cast<VkBool32>( primitiveRestartEnable ) );
  }

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
  //=== VK_QNX_screen_surface ===


  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE Result Instance::createScreenSurfaceQNX( const VULKAN_HPP_NAMESPACE::ScreenSurfaceCreateInfoQNX * pCreateInfo, const VULKAN_HPP_NAMESPACE::AllocationCallbacks * pAllocator, VULKAN_HPP_NAMESPACE::SurfaceKHR * pSurface, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Result>( d.vkCreateScreenSurfaceQNX( m_instance, reinterpret_cast<const VkScreenSurfaceCreateInfoQNX *>( pCreateInfo ), reinterpret_cast<const VkAllocationCallbacks *>( pAllocator ), reinterpret_cast<VkSurfaceKHR *>( pSurface ) ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<VULKAN_HPP_NAMESPACE::SurfaceKHR >::type Instance::createScreenSurfaceQNX( const VULKAN_HPP_NAMESPACE::ScreenSurfaceCreateInfoQNX & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::SurfaceKHR  surface;
    Result result = static_cast<Result>( d.vkCreateScreenSurfaceQNX( m_instance, reinterpret_cast<const VkScreenSurfaceCreateInfoQNX *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    return createResultValue( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createScreenSurfaceQNX" );
  }

#  ifndef VULKAN_HPP_NO_SMART_HANDLE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD_WHEN_NO_EXCEPTIONS VULKAN_HPP_INLINE typename ResultValueType<UniqueHandle<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>>::type Instance::createScreenSurfaceQNXUnique( const VULKAN_HPP_NAMESPACE::ScreenSurfaceCreateInfoQNX & createInfo, Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    VULKAN_HPP_NAMESPACE::SurfaceKHR surface;
    Result result = static_cast<Result>( d.vkCreateScreenSurfaceQNX( m_instance, reinterpret_cast<const VkScreenSurfaceCreateInfoQNX *>( &createInfo ), reinterpret_cast<const VkAllocationCallbacks *>( static_cast<const VULKAN_HPP_NAMESPACE::AllocationCallbacks *>( allocator ) ), reinterpret_cast<VkSurfaceKHR *>( &surface ) ) );
    ObjectDestroy<Instance, Dispatch> deleter( *this, allocator, d );
    return createResultValue<VULKAN_HPP_NAMESPACE::SurfaceKHR, Dispatch>( result, surface, VULKAN_HPP_NAMESPACE_STRING "::Instance::createScreenSurfaceQNXUnique", deleter );
  }
#  endif /*VULKAN_HPP_NO_SMART_HANDLE*/
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getScreenPresentationSupportQNX( uint32_t queueFamilyIndex, struct _screen_window * window, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    return static_cast<Bool32>( d.vkGetPhysicalDeviceScreenPresentationSupportQNX( m_physicalDevice, queueFamilyIndex, window ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE Bool32 PhysicalDevice::getScreenPresentationSupportQNX( uint32_t queueFamilyIndex, struct _screen_window & window, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    return d.vkGetPhysicalDeviceScreenPresentationSupportQNX( m_physicalDevice, queueFamilyIndex, &window );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

  //=== VK_EXT_color_write_enable ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setColorWriteEnableEXT( uint32_t attachmentCount, const VULKAN_HPP_NAMESPACE::Bool32 * pColorWriteEnables, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdSetColorWriteEnableEXT( m_commandBuffer, attachmentCount, reinterpret_cast<const VkBool32 *>( pColorWriteEnables ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::setColorWriteEnableEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::Bool32> const & colorWriteEnables, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdSetColorWriteEnableEXT( m_commandBuffer, colorWriteEnables.size(), reinterpret_cast<const VkBool32 *>( colorWriteEnables.data() ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_multi_draw ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMultiEXT( uint32_t drawCount, const VULKAN_HPP_NAMESPACE::MultiDrawInfoEXT * pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawMultiEXT( m_commandBuffer, drawCount, reinterpret_cast<const VkMultiDrawInfoEXT *>( pVertexInfo ), instanceCount, firstInstance, stride );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMultiEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::MultiDrawInfoEXT> const & vertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdDrawMultiEXT( m_commandBuffer, vertexInfo.size(), reinterpret_cast<const VkMultiDrawInfoEXT *>( vertexInfo.data() ), instanceCount, firstInstance, stride );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMultiIndexedEXT( uint32_t drawCount, const VULKAN_HPP_NAMESPACE::MultiDrawIndexedInfoEXT * pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t * pVertexOffset, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkCmdDrawMultiIndexedEXT( m_commandBuffer, drawCount, reinterpret_cast<const VkMultiDrawIndexedInfoEXT *>( pIndexInfo ), instanceCount, firstInstance, stride, pVertexOffset );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_INLINE void CommandBuffer::drawMultiIndexedEXT( ArrayProxy<const VULKAN_HPP_NAMESPACE::MultiDrawIndexedInfoEXT> const & indexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, Optional<const int32_t> vertexOffset, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    
    d.vkCmdDrawMultiIndexedEXT( m_commandBuffer, indexInfo.size(), reinterpret_cast<const VkMultiDrawIndexedInfoEXT *>( indexInfo.data() ), instanceCount, firstInstance, stride, static_cast<const int32_t *>( vertexOffset ) );
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_EXT_pageable_device_local_memory ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::setMemoryPriorityEXT( VULKAN_HPP_NAMESPACE::DeviceMemory memory, float priority, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkSetDeviceMemoryPriorityEXT( m_device, static_cast<VkDeviceMemory>( memory ), priority );
  }

  //=== VK_KHR_maintenance4 ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getBufferMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceBufferMemoryRequirements * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceBufferMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceBufferMemoryRequirements *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getBufferMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceBufferMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetDeviceBufferMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceBufferMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getBufferMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceBufferMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetDeviceBufferMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceBufferMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements * pInfo, VULKAN_HPP_NAMESPACE::MemoryRequirements2 * pMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceImageMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( pInfo ), reinterpret_cast<VkMemoryRequirements2 *>( pMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::MemoryRequirements2  Device::getImageMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::MemoryRequirements2  memoryRequirements;
    d.vkGetDeviceImageMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return memoryRequirements;
  }

  template <typename X, typename Y, typename... Z, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE StructureChain<X, Y, Z...> Device::getImageMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    StructureChain<X, Y, Z...> structureChain;
    VULKAN_HPP_NAMESPACE::MemoryRequirements2 & memoryRequirements = structureChain.template get<VULKAN_HPP_NAMESPACE::MemoryRequirements2>();
    d.vkGetDeviceImageMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), reinterpret_cast<VkMemoryRequirements2 *>( &memoryRequirements ) );
    return structureChain;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getImageSparseMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements * pInfo, uint32_t * pSparseMemoryRequirementCount, VULKAN_HPP_NAMESPACE::SparseImageMemoryRequirements2 * pSparseMemoryRequirements, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDeviceImageSparseMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( pInfo ), pSparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( pSparseMemoryRequirements ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements;
    uint32_t sparseMemoryRequirementCount;
    d.vkGetDeviceImageSparseMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetDeviceImageSparseMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }

  template <typename SparseImageMemoryRequirements2Allocator, typename Dispatch, typename B, typename std::enable_if<std::is_same<typename B::value_type, SparseImageMemoryRequirements2>::value, int>::type >
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> Device::getImageSparseMemoryRequirementsKHR( const VULKAN_HPP_NAMESPACE::DeviceImageMemoryRequirements & info, SparseImageMemoryRequirements2Allocator & sparseImageMemoryRequirements2Allocator, Dispatch const & d ) const
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    std::vector<SparseImageMemoryRequirements2, SparseImageMemoryRequirements2Allocator> sparseMemoryRequirements( sparseImageMemoryRequirements2Allocator );
    uint32_t sparseMemoryRequirementCount;
    d.vkGetDeviceImageSparseMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, nullptr );
    sparseMemoryRequirements.resize( sparseMemoryRequirementCount );
    d.vkGetDeviceImageSparseMemoryRequirementsKHR( m_device, reinterpret_cast<const VkDeviceImageMemoryRequirements *>( &info ), &sparseMemoryRequirementCount, reinterpret_cast<VkSparseImageMemoryRequirements2 *>( sparseMemoryRequirements.data() ) );
    VULKAN_HPP_ASSERT( sparseMemoryRequirementCount <= sparseMemoryRequirements.size() );
    return sparseMemoryRequirements;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/

  //=== VK_VALVE_descriptor_set_host_mapping ===


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getDescriptorSetLayoutHostMappingInfoVALVE( const VULKAN_HPP_NAMESPACE::DescriptorSetBindingReferenceVALVE * pBindingReference, VULKAN_HPP_NAMESPACE::DescriptorSetLayoutHostMappingInfoVALVE * pHostMapping, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDescriptorSetLayoutHostMappingInfoVALVE( m_device, reinterpret_cast<const VkDescriptorSetBindingReferenceVALVE *>( pBindingReference ), reinterpret_cast<VkDescriptorSetLayoutHostMappingInfoVALVE *>( pHostMapping ) );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE VULKAN_HPP_NAMESPACE::DescriptorSetLayoutHostMappingInfoVALVE  Device::getDescriptorSetLayoutHostMappingInfoVALVE( const VULKAN_HPP_NAMESPACE::DescriptorSetBindingReferenceVALVE & bindingReference, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    VULKAN_HPP_NAMESPACE::DescriptorSetLayoutHostMappingInfoVALVE  hostMapping;
    d.vkGetDescriptorSetLayoutHostMappingInfoVALVE( m_device, reinterpret_cast<const VkDescriptorSetBindingReferenceVALVE *>( &bindingReference ), reinterpret_cast<VkDescriptorSetLayoutHostMappingInfoVALVE *>( &hostMapping ) );
    return hostMapping;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  template <typename Dispatch>
  VULKAN_HPP_INLINE void Device::getDescriptorSetHostMappingVALVE( VULKAN_HPP_NAMESPACE::DescriptorSet descriptorSet, void ** ppData, Dispatch const & d  ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );
    d.vkGetDescriptorSetHostMappingVALVE( m_device, static_cast<VkDescriptorSet>( descriptorSet ), ppData );
  }

#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE
  template <typename Dispatch>
  VULKAN_HPP_NODISCARD VULKAN_HPP_INLINE void * Device::getDescriptorSetHostMappingVALVE( VULKAN_HPP_NAMESPACE::DescriptorSet descriptorSet, Dispatch const & d ) const VULKAN_HPP_NOEXCEPT
  {
    VULKAN_HPP_ASSERT( d.getVkHeaderVersion() == VK_HEADER_VERSION );

    void * pData;
    d.vkGetDescriptorSetHostMappingVALVE( m_device, static_cast<VkDescriptorSet>( descriptorSet ), &pData );
    return pData;
  }
#endif /*VULKAN_HPP_DISABLE_ENHANCED_MODE*/


  }   // namespace VULKAN_HPP_NAMESPACE
#endif
