using UnityEngine;

public static class ExtensionMethods
{
    public static Sprite ConvertToSprite(this Texture2D img)
    {
        return Sprite.Create(img, new Rect(0, 0, img.width, img.height), Vector2.zero);
    }

    public static void Spawn(this Transform trans, Transform spawnPoint)
    {
        trans.position = spawnPoint.position;
        trans.rotation = spawnPoint.rotation;
        trans.gameObject.SetActive(true);
    }
}
