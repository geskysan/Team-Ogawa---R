using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishingController : MonoBehaviour {

    [SerializeField] GirlsManager girlsManager;
    [SerializeField] ScoreManager scoreManager;
    [SerializeField] int[] m_GirlScore;

    public void OnCollisionEnter2D(Collision2D collision)
    {

        if(collision.gameObject.tag == "Girl01")
        {
            scoreManager.m_Score += m_GirlScore[0];
            Debug.Log("+" + m_GirlScore[0]);
        }

        if (collision.gameObject.tag == "Girl02")
        {
            scoreManager.m_Score += m_GirlScore[1];
            Debug.Log("+" + m_GirlScore[1]);
        }

        if (collision.gameObject.tag == "Girl03")
        {
            scoreManager.m_Score += m_GirlScore[2];
            Debug.Log("+" + m_GirlScore[2]);
        }

        this.gameObject.transform.localPosition = new Vector3(-500f, -500f, 0f);

        // 接触したオブジェクトとルアーを非表示
        Destroy(collision.gameObject);
        this.gameObject.SetActive(false);

        // 減った分の女の子生成
        girlsManager.GirlSpawn();
    }
}
