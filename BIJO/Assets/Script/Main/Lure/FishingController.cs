using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishingController : MonoBehaviour {

    [SerializeField] GirlsManager girlsManager;

    /// <summary>
    /// 接触した美女を判定し、スコアに加算する
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionEnter2D(Collision2D collision)
    {
        // 接触したオブジェクトのタグを渡す
        girlsManager.GirlCounter(collision.gameObject.tag);

        // 接触したオブジェクトが壁でなかったなら
        if(collision.gameObject.tag != "wall")
        {
            // 接触したオブジェクトとルアーを非表示
            Destroy(collision.gameObject);

            // 場にいる美女の数を１つ減らす
            girlsManager.m_girlsCount--;

            // ルアーの座標をリセット
            this.gameObject.GetComponent<LureController>().LureReset();
        }
    }
}