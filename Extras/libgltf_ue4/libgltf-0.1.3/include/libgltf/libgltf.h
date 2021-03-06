#pragma once

#include <stdint.h>
#include <vector>
#include <map>
#include <string>
#include <memory>

#define LIBGLTF_MAJOR_VERSION    0
#define LIBGLTF_MINOR_VERSION    1
#define LIBGLTF_PATCH_VERSION    2

#if defined(UNICODE)
typedef std::wstring                                        GLTFString;
#else
typedef std::string                                         GLTFString;
#endif

namespace libgltf
{
    struct SGlTF;
    bool operator<<(std::shared_ptr<SGlTF>& _pGlTF, const GLTFString& _sContent);
    bool operator>>(const std::shared_ptr<SGlTF>& _pGlTF, GLTFString& _sContent);
    struct SObject
    {
        SObject();
        GLTFString schemaType;
    };

    /*!
     * struct: SGlTFProperty
     */
    struct SGlTFProperty : SObject
    {
        SGlTFProperty();

        // Check valid
        operator bool() const;

        std::shared_ptr<struct SExtras> extras;
        std::shared_ptr<struct SExtension> extensions;
    };

    /*!
     * struct: SGlTFChildofRootProperty
     */
    struct SGlTFChildofRootProperty : SGlTFProperty
    {
        SGlTFChildofRootProperty();

        // Check valid
        operator bool() const;

        // The user-defined name of this object.
        GLTFString name;
    };

    /*!
     * struct: SMaterial
     * The material appearance of a primitive.
     */
    struct SMaterial : SGlTFChildofRootProperty
    {
        SMaterial();

        // Check valid
        operator bool() const;

        // The alpha cutoff value of the material.
        float alphaCutoff;
        // The emissive map texture.
        std::shared_ptr<struct STextureInfo> emissiveTexture;
        // A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology. When not specified, all the default values of `pbrMetallicRoughness` apply.
        std::shared_ptr<struct SMaterialPBRMetallicRoughness> pbrMetallicRoughness;
        // The occlusion map texture.
        std::shared_ptr<struct SMaterialOcclusionTextureInfo> occlusionTexture;
        // The alpha rendering mode of the material.
        GLTFString alphaMode;
        // Specifies whether the material is double sided.
        bool doubleSided;
        // The normal map texture.
        std::shared_ptr<struct SMaterialNormalTextureInfo> normalTexture;
        // The emissive color of the material.
        std::vector<float> emissiveFactor;
    };

    /*!
     * struct: SAsset
     * Metadata about the glTF asset.
     */
    struct SAsset : SGlTFProperty
    {
        SAsset();

        // Check valid
        operator bool() const;

        // The minimum glTF version that this asset targets.
        GLTFString minVersion;
        // The glTF version that this asset targets.
        GLTFString version;
        // Tool that generated this glTF model.  Useful for debugging.
        GLTFString generator;
        // A copyright message suitable for display to credit the content creator.
        GLTFString copyright;
    };

    /*!
     * struct: SSampler
     * Texture sampler properties for filtering and wrapping modes.
     */
    struct SSampler : SGlTFChildofRootProperty
    {
        SSampler();

        // Check valid
        operator bool() const;

        // s wrapping mode.
        int32_t wrapS;
        // Minification filter.
        int32_t minFilter;
        // Magnification filter.
        int32_t magFilter;
        // t wrapping mode.
        int32_t wrapT;
    };

    /*!
     * struct: SAnimationSampler
     * Combines input and output accessors with an interpolation algorithm to define a keyframe graph (but not its target).
     */
    struct SAnimationSampler : SGlTFProperty
    {
        SAnimationSampler();

        // Check valid
        operator bool() const;

        // The index of an accessor containing keyframe input values, e.g., time.
        std::shared_ptr<struct SGlTFId> input;
        // The index of an accessor, containing keyframe output values.
        std::shared_ptr<struct SGlTFId> output;
        // Interpolation algorithm.
        GLTFString interpolation;
    };

    /*!
     * struct: SExtras
     * Application-specific data.
     */
    struct SExtras : SObject
    {
        SExtras();

        // Check valid
        operator bool() const;
    };

    /*!
     * struct: SScene
     * The root nodes of a scene.
     */
    struct SScene : SGlTFChildofRootProperty
    {
        SScene();

        // Check valid
        operator bool() const;

        // The indices of each root node.
        std::vector<std::shared_ptr<struct SGlTFId>> nodes;
    };

    /*!
     * struct: SCameraPerspective
     * A perspective camera containing properties to create a perspective projection matrix.
     */
    struct SCameraPerspective : SGlTFProperty
    {
        SCameraPerspective();

        // Check valid
        operator bool() const;

        // The floating-point aspect ratio of the field of view.
        float aspectRatio;
        // The floating-point vertical field of view in radians.
        float yfov;
        // The floating-point distance to the near clipping plane.
        float znear;
        // The floating-point distance to the far clipping plane.
        float zfar;
    };

    /*!
     * struct: SBufferView
     * A view into a buffer generally representing a subset of the buffer.
     */
    struct SBufferView : SGlTFChildofRootProperty
    {
        SBufferView();

        // Check valid
        operator bool() const;

        // The length of the bufferView in bytes.
        int32_t byteLength;
        // The index of the buffer.
        std::shared_ptr<struct SGlTFId> buffer;
        // The offset into the buffer in bytes.
        int32_t byteOffset;
        // The target that the GPU buffer should be bound to.
        int32_t target;
        // The stride, in bytes.
        int32_t byteStride;
    };

    /*!
     * struct: STextureInfo
     * Reference to a texture.
     */
    struct STextureInfo : SGlTFProperty
    {
        STextureInfo();

        // Check valid
        operator bool() const;

        // The index of the texture.
        std::shared_ptr<struct SGlTFId> index;
        // The set index of texture's TEXCOORD attribute used for texture coordinate mapping.
        int32_t texCoord;
    };

    /*!
     * struct: SMaterialNormalTextureInfo
     */
    struct SMaterialNormalTextureInfo : STextureInfo
    {
        SMaterialNormalTextureInfo();

        // Check valid
        operator bool() const;

        // The scalar multiplier applied to each normal vector of the normal texture.
        float scale;
    };

    /*!
     * struct: SMaterialOcclusionTextureInfo
     */
    struct SMaterialOcclusionTextureInfo : STextureInfo
    {
        SMaterialOcclusionTextureInfo();

        // Check valid
        operator bool() const;

        // A scalar multiplier controlling the amount of occlusion applied.
        float strength;
    };

    /*!
     * struct: SAccessorSparseValues
     * Array of size `accessor.sparse.count` times number of components storing the displaced accessor attributes pointed by `accessor.sparse.indices`.
     */
    struct SAccessorSparseValues : SGlTFProperty
    {
        SAccessorSparseValues();

        // Check valid
        operator bool() const;

        // The index of the bufferView with sparse values. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target.
        std::shared_ptr<struct SGlTFId> bufferView;
        // The offset relative to the start of the bufferView in bytes. Must be aligned.
        int32_t byteOffset;
    };

    /*!
     * struct: SAnimationChannelTarget
     * The index of the node and TRS property that an animation channel targets.
     */
    struct SAnimationChannelTarget : SGlTFProperty
    {
        SAnimationChannelTarget();

        // Check valid
        operator bool() const;

        // The index of the node to target.
        std::shared_ptr<struct SGlTFId> node;
        // The name of the node's TRS property to modify, or the "weights" of the Morph Targets it instantiates. For the "translation" property, the values that are provided by the sampler are the translation along the x, y, and z axes. For the "rotation" property, the values are a quaternion in the order (x, y, z, w), where w is the scalar. For the "scale" property, the values are the scaling factors along the x, y, and z axes.
        GLTFString path;
    };

    /*!
     * struct: SMesh
     * A set of primitives to be rendered.  A node can contain one mesh.  A node's transform places the mesh in the scene.
     */
    struct SMesh : SGlTFChildofRootProperty
    {
        SMesh();

        // Check valid
        operator bool() const;

        // An array of primitives, each defining geometry to be rendered with a material.
        std::vector<std::shared_ptr<struct SMeshPrimitive>> primitives;
        // Array of weights to be applied to the Morph Targets.
        std::vector<float> weights;
    };

    /*!
     * struct: SAccessorSparse
     * Sparse storage of attributes that deviate from their initialization value.
     */
    struct SAccessorSparse : SGlTFProperty
    {
        SAccessorSparse();

        // Check valid
        operator bool() const;

        // Number of entries stored in the sparse array.
        int32_t count;
        // Index array of size `count` that points to those accessor attributes that deviate from their initialization value. Indices must strictly increase.
        std::shared_ptr<struct SAccessorSparseIndices> indices;
        // Array of size `count` times number of components, storing the displaced accessor attributes pointed by `indices`. Substituted values must have the same `componentType` and number of components as the base accessor.
        std::shared_ptr<struct SAccessorSparseValues> values;
    };

    /*!
     * struct: SMeshPrimitive
     * Geometry to be rendered with the given material.
     */
    struct SMeshPrimitive : SGlTFProperty
    {
        SMeshPrimitive();

        // Check valid
        operator bool() const;

        // The index of the accessor that contains the indices.
        std::shared_ptr<struct SGlTFId> indices;
        // A dictionary object, where each key corresponds to mesh attribute semantic and each value is the index of the accessor containing attribute's data.
        std::map<GLTFString, std::shared_ptr<struct SGlTFId>> attributes;
        // The index of the material to apply to this primitive when rendering.
        std::shared_ptr<struct SGlTFId> material;
        // The type of primitives to render.
        int32_t mode;
        // An array of Morph Targets, each  Morph Target is a dictionary mapping attributes (only `POSITION`, `NORMAL`, and `TANGENT` supported) to their deviations in the Morph Target.
        std::vector<std::shared_ptr<struct SGlTFId>> targets;
    };

    /*!
     * struct: SKHR_materials_pbrSpecularGlossinessglTFextension
     * glTF extension that defines the specular-glossiness material model from Physically-Based Rendering (PBR) methodology.
     */
    struct SKHR_materials_pbrSpecularGlossinessglTFextension : SGlTFProperty
    {
        SKHR_materials_pbrSpecularGlossinessglTFextension();

        // Check valid
        operator bool() const;

        // The specular RGB color of the material.
        std::vector<float> specularFactor;
        // The glossiness or smoothness of the material.
        float glossinessFactor;
        // The diffuse texture.
        std::shared_ptr<struct STextureInfo> diffuseTexture;
        // The specular-glossiness texture.
        std::shared_ptr<struct STextureInfo> specularGlossinessTexture;
        // The reflected diffuse factor of the material.
        std::vector<float> diffuseFactor;
    };

    /*!
     * struct: SExtension
     * Dictionary object with extension-specific objects.
     */
    struct SExtension : SObject
    {
        SExtension();

        // Check valid
        operator bool() const;

        // Manual code lines
        std::map<GLTFString, std::shared_ptr<struct SObject>> properties;
    };

    /*!
     * struct: SAnimationChannel
     * Targets an animation's sampler at a node's property.
     */
    struct SAnimationChannel : SGlTFProperty
    {
        SAnimationChannel();

        // Check valid
        operator bool() const;

        // The index of the node and TRS property to target.
        std::shared_ptr<struct SAnimationChannelTarget> target;
        // The index of a sampler in this animation used to compute the value for the target.
        std::shared_ptr<struct SGlTFId> sampler;
    };

    /*!
     * struct: SGlTFId
     */
    struct SGlTFId : SObject
    {
        SGlTFId();

        // Check valid
        operator bool() const;

        operator int32_t() const;

        int32_t int32_tValue;
    };

    /*!
     * struct: SAccessorSparseIndices
     * Indices of those attributes that deviate from their initialization value.
     */
    struct SAccessorSparseIndices : SGlTFProperty
    {
        SAccessorSparseIndices();

        // Check valid
        operator bool() const;

        // The indices data type.
        int32_t componentType;
        // The index of the bufferView with sparse indices. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target.
        std::shared_ptr<struct SGlTFId> bufferView;
        // The offset relative to the start of the bufferView in bytes. Must be aligned.
        int32_t byteOffset;
    };

    /*!
     * struct: SNode
     * A node in the node hierarchy.  When the node contains `skin`, all `mesh.primitives` must contain `JOINTS_0` and `WEIGHTS_0` attributes.  A node can have either a `matrix` or any combination of `translation`/`rotation`/`scale` (TRS) properties. TRS properties are converted to matrices and postmultiplied in the `T * R * S` order to compose the transformation matrix; first the scale is applied to the vertices, then the rotation, and then the translation. If none are provided, the transform is the identity. When a node is targeted for animation (referenced by an animation.channel.target), only TRS properties may be present; `matrix` will not be present.
     */
    struct SNode : SGlTFChildofRootProperty
    {
        SNode();

        // Check valid
        operator bool() const;

        // The node's non-uniform scale, given as the scaling factors along the x, y, and z axes.
        std::vector<float> scale;
        // The node's unit quaternion rotation in the order (x, y, z, w), where w is the scalar.
        std::vector<float> rotation;
        // A floating-point 4x4 transformation matrix stored in column-major order.
        std::vector<float> matrix;
        // The index of the mesh in this node.
        std::shared_ptr<struct SGlTFId> mesh;
        // The index of the camera referenced by this node.
        std::shared_ptr<struct SGlTFId> camera;
        // The weights of the instantiated Morph Target. Number of elements must match number of Morph Targets of used mesh.
        std::vector<float> weights;
        // The index of the skin referenced by this node.
        std::shared_ptr<struct SGlTFId> skin;
        // The node's translation along the x, y, and z axes.
        std::vector<float> translation;
        // The indices of this node's children.
        std::vector<std::shared_ptr<struct SGlTFId>> children;
    };

    /*!
     * struct: SAnimation
     * A keyframe animation.
     */
    struct SAnimation : SGlTFChildofRootProperty
    {
        SAnimation();

        // Check valid
        operator bool() const;

        // An array of channels, each of which targets an animation's sampler at a node's property. Different channels of the same animation can't have equal targets.
        std::vector<std::shared_ptr<struct SAnimationChannel>> channels;
        // An array of samplers that combines input and output accessors with an interpolation algorithm to define a keyframe graph (but not its target).
        std::vector<std::shared_ptr<struct SAnimationSampler>> samplers;
    };

    /*!
     * struct: SSkin
     * Joints and matrices defining a skin.
     */
    struct SSkin : SGlTFChildofRootProperty
    {
        SSkin();

        // Check valid
        operator bool() const;

        // Indices of skeleton nodes, used as joints in this skin.
        std::vector<std::shared_ptr<struct SGlTFId>> joints;
        // The index of the accessor containing the floating-point 4x4 inverse-bind matrices.  The default is that each matrix is a 4x4 identity matrix, which implies that inverse-bind matrices were pre-applied.
        std::shared_ptr<struct SGlTFId> inverseBindMatrices;
        // The index of the node used as a skeleton root. When undefined, joints transforms resolve to scene root.
        std::shared_ptr<struct SGlTFId> skeleton;
    };

    /*!
     * struct: SMaterialPBRMetallicRoughness
     * A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology.
     */
    struct SMaterialPBRMetallicRoughness : SGlTFProperty
    {
        SMaterialPBRMetallicRoughness();

        // Check valid
        operator bool() const;

        // The roughness of the material.
        float roughnessFactor;
        // The base color texture.
        std::shared_ptr<struct STextureInfo> baseColorTexture;
        // The metalness of the material.
        float metallicFactor;
        // The material's base color factor.
        std::vector<float> baseColorFactor;
        // The metallic-roughness texture.
        std::shared_ptr<struct STextureInfo> metallicRoughnessTexture;
    };

    /*!
     * struct: SKHR_draco_mesh_compressionextension
     */
    struct SKHR_draco_mesh_compressionextension : SObject
    {
        SKHR_draco_mesh_compressionextension();

        // Check valid
        operator bool() const;

        // A dictionary object, where each key corresponds to an attribute and its unique attribute id stored in the compressed geometry.
        std::map<GLTFString, std::shared_ptr<struct SGlTFId>> attributes;
        // The index of the bufferView.
        std::shared_ptr<struct SGlTFId> bufferView;
    };

    /*!
     * struct: SCamera
     * A camera's projection.  A node can reference a camera to apply a transform to place the camera in the scene.
     */
    struct SCamera : SGlTFChildofRootProperty
    {
        SCamera();

        // Check valid
        operator bool() const;

        // Specifies if the camera uses a perspective or orthographic projection.
        GLTFString type;
        // A perspective camera containing properties to create a perspective projection matrix.
        std::shared_ptr<struct SCameraPerspective> perspective;
        // An orthographic camera containing properties to create an orthographic projection matrix.
        std::shared_ptr<struct SCameraOrthographic> orthographic;
    };

    /*!
     * struct: SImage
     * Image data used to create a texture. Image can be referenced by URI or `bufferView` index. `mimeType` is required in the latter case.
     */
    struct SImage : SGlTFChildofRootProperty
    {
        SImage();

        // Check valid
        operator bool() const;

        // The image's MIME type.
        GLTFString mimeType;
        // The index of the bufferView that contains the image. Use this instead of the image's uri property.
        std::shared_ptr<struct SGlTFId> bufferView;
        // The uri of the image.
        GLTFString uri;
    };

    /*!
     * struct: STexture
     * A texture and its sampler.
     */
    struct STexture : SGlTFChildofRootProperty
    {
        STexture();

        // Check valid
        operator bool() const;

        // The index of the image used by this texture.
        std::shared_ptr<struct SGlTFId> source;
        // The index of the sampler used by this texture. When undefined, a sampler with repeat wrapping and auto filtering should be used.
        std::shared_ptr<struct SGlTFId> sampler;
    };

    /*!
     * struct: SCameraOrthographic
     * An orthographic camera containing properties to create an orthographic projection matrix.
     */
    struct SCameraOrthographic : SGlTFProperty
    {
        SCameraOrthographic();

        // Check valid
        operator bool() const;

        // The floating-point horizontal magnification of the view. Must not be zero.
        float xmag;
        // The floating-point vertical magnification of the view. Must not be zero.
        float ymag;
        // The floating-point distance to the far clipping plane. `zfar` must be greater than `znear`.
        float zfar;
        // The floating-point distance to the near clipping plane.
        float znear;
    };

    /*!
     * struct: SBuffer
     * A buffer points to binary geometry, animation, or skins.
     */
    struct SBuffer : SGlTFChildofRootProperty
    {
        SBuffer();

        // Check valid
        operator bool() const;

        // The length of the buffer in bytes.
        int32_t byteLength;
        // The uri of the buffer.
        GLTFString uri;
    };

    /*!
     * struct: SAccessor
     * A typed view into a bufferView.  A bufferView contains raw binary data.  An accessor provides a typed view into a bufferView or a subset of a bufferView similar to how WebGL's `vertexAttribPointer()` defines an attribute in a buffer.
     */
    struct SAccessor : SGlTFChildofRootProperty
    {
        SAccessor();

        // Check valid
        operator bool() const;

        // The number of attributes referenced by this accessor.
        int32_t count;
        // Minimum value of each component in this attribute.
        std::vector<float> min;
        // Maximum value of each component in this attribute.
        std::vector<float> max;
        // The index of the bufferView.
        std::shared_ptr<struct SGlTFId> bufferView;
        // The datatype of components in the attribute.
        int32_t componentType;
        // The offset relative to the start of the bufferView in bytes.
        int32_t byteOffset;
        // Sparse storage of attributes that deviate from their initialization value.
        std::shared_ptr<struct SAccessorSparse> sparse;
        // Specifies if the attribute is a scalar, vector, or matrix.
        GLTFString type;
        // Specifies whether integer data values should be normalized.
        bool normalized;
    };

    /*!
     * struct: SGlTF
     * The root object for a glTF asset.
     */
    struct SGlTF : SGlTFProperty
    {
        SGlTF();

        // Check valid
        operator bool() const;

        // An array of textures.
        std::vector<std::shared_ptr<struct STexture>> textures;
        // An array of cameras.
        std::vector<std::shared_ptr<struct SCamera>> cameras;
        // An array of accessors.
        std::vector<std::shared_ptr<struct SAccessor>> accessors;
        // Names of glTF extensions used somewhere in this asset.
        std::vector<GLTFString> extensionsUsed;
        // An array of samplers.
        std::vector<std::shared_ptr<struct SSampler>> samplers;
        // An array of scenes.
        std::vector<std::shared_ptr<struct SScene>> scenes;
        // The index of the default scene.
        std::shared_ptr<struct SGlTFId> scene;
        // Names of glTF extensions required to properly load this asset.
        std::vector<GLTFString> extensionsRequired;
        // An array of meshes.
        std::vector<std::shared_ptr<struct SMesh>> meshes;
        // An array of keyframe animations.
        std::vector<std::shared_ptr<struct SAnimation>> animations;
        // An array of images.
        std::vector<std::shared_ptr<struct SImage>> images;
        // An array of nodes.
        std::vector<std::shared_ptr<struct SNode>> nodes;
        // An array of bufferViews.
        std::vector<std::shared_ptr<struct SBufferView>> bufferViews;
        // An array of skins.
        std::vector<std::shared_ptr<struct SSkin>> skins;
        // An array of materials.
        std::vector<std::shared_ptr<struct SMaterial>> materials;
        // An array of buffers.
        std::vector<std::shared_ptr<struct SBuffer>> buffers;
        // Metadata about the glTF asset.
        std::shared_ptr<struct SAsset> asset;
    };

}
