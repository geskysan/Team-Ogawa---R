using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LureImageChange : MonoBehaviour {

    enum LURETUPE
    {
        cookie,
        money,
        flower,
        cat,
        car,
        ring,
        jewelry,
        wallet,
        lotion,
        perfume,
        Tablet,
        Cake,
    }

    [SerializeField] LURETUPE m_lureType;

    [SerializeField] Sprite[] m_lureImage;

    [SerializeField] GameObject[] obj;

    private void Start()
    {
        for (int i = 0; i < m_lureImage.Length; i++)
        {
            if (m_lureType == LURETUPE.cookie + i)
            {
                for (int j = 0; j < obj.Length; j++)
                    obj[j].GetComponent<Image>().sprite = m_lureImage[i];
            }
        }

        // ルアーのサイズを取得
        var objSize = obj[1].GetComponent<RectTransform>().sizeDelta;
        var collision = obj[1].GetComponent<BoxCollider2D>();

        // BoxColliderのサイズをルアーのサイズに合わせる
        collision.size = objSize;
    }
}
