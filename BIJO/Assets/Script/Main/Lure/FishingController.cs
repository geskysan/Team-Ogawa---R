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
        // 接触したオブジェクトが壁でなかったなら
        if(collision.gameObject.tag != "wall")
        {
            // ランダムでSEを流す
            var random = Random.Range(0, 4);
            if (random == 0)
                SoundScript.Instance.PlaySE(SoundNameData.SE_GET01);

            else if (random == 1)
                SoundScript.Instance.PlaySE(SoundNameData.SE_GET02);

            else if (random == 2)
                SoundScript.Instance.PlaySE(SoundNameData.SE_GET03);

            else if (random == 3)
                SoundScript.Instance.PlaySE(SoundNameData.SE_GET04);

            // パーティクル発動
            var loveParticle = Resources.Load("Particle/Love") as GameObject;
            Instantiate(loveParticle, collision.transform.position, Quaternion.identity);

            // 美女をカウント
            girlsManager.GirlCounter(collision.gameObject.tag);

            // 接触したオブジェクトとルアーを非表示
            Destroy(collision.gameObject);

            // 場にいる美女の数を１つ減らす
            girlsManager.m_girlsCount--;

            // ルアーの座標をリセット
            this.gameObject.GetComponent<LureController>().LureReset();
        }
    }
}