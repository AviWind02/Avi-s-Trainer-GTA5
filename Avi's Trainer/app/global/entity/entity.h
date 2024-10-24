#pragma once
namespace g_feature {
    namespace g_entity {

        void ApplyForce(Entity entityHandle, Vector3 direction, Vector3 offset, int forceType);
        void ApplyForce(Entity entityHandle, Vector3 direction, int forceType);
        void Oscillate(Entity entityHandle, const Vector3& position, float angleFrequency, float dampingRatio);
        void ApplyForceForwardFromWeapon(Entity entityHandle, float force);
        void ApplyForceForwardCam(Entity entityHandle, float force);
        Object SetRope(Entity startEntity, Entity endEntity);
        int GetRay(BOOL* hit, Vector3* endCoords, Vector3* surfaceNormal, Entity* entityHit, bool* isEntityReal);
        int GetObjectPlayerLookingAt(Entity* entity, bool* isEntityReal);
        int GetCoordsPlayerLookingAt(Vector3* endCoords);
        void SpawnObject(Object* obj, const char* objectHash, Vector3 coords);
        void AttachObjects(Entity e1, Entity e2, Vector3 coords);
        void AttachObject(Entity e1, const char* objectHash);
        Vector3 GetGameplayCamRot();
        Vector3 GetGameplayCamCoords();
        void SetCoords(Entity entity, Vector3 coord);
        std::uint64_t GetEntityAddress(Entity handle);
        void SetGravity(Entity handle, float value);
        float GetGravity(Entity handle);
    }
}