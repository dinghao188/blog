<template>
  <div class="validate_container">
    <form class="validate_form">
      <section v-if="needWhat.phoneNumber" class="input_container" id="phoneInputContainer">
        <div class="image_in_input">
          <svg><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-login-account"></use></svg>
        </div>
        <input v-model="phoneNumber" type="text" class="phone_input" maxLength="11" placeholder="请输入手机号" >
        <div class="image_in_input">
          <svg class="s_svg clear-icon" v-show="phoneNumber" @click="clearInput('phoneNumber')"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-login-clear"></use></svg>
        </div>
      </section>
      <section v-if="needWhat.imgCode" class="input_container" id="imgCodeContainer">
        <div class="image_in_input">
          <svg><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-register-img"></use></svg>
        </div>
        <input v-model="imgCode" type="text" maxLength="4" class="img_code_input" placeholder="请输入右图结果">
        <div class="image_in_input">
          <svg class="s_svg clear-icon" v-show="imgCode" @click="clearInput('imgCode')"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-login-clear"></use></svg>
        </div>
        <button class="img_code_get">
          <svg><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-register-refresh"></use></svg>
          <span class="btn_txt">点击刷新</span>
        </button>
        <!-- <button class="img_code_get">
          <img class="img_code" :src="img">
        </button> -->
      </section>
      <section v-if="needWhat.smsCode" class="input_container" id="smsCodeContainer">
        <div class="image_in_input">
          <svg><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-login-security"></use></svg>
        </div>
        <input v-model="smsCode" type="text" class="sms_code_input" maxLength="6" placeholder="短信验证码">
        <div class="image_in_input">
          <svg class="s_svg clear-icon" v-show="smsCode" @click="clearInput('smsCode')"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#icon-login-clear"></use></svg>
        </div>
        <button class="sms_code_get">获取验证码</button>
      </section>
      <section class="hint_container"></section>
    </form>
    <section class="btn_container">
      <button class="go_next_btn">绑定</button>
    </section>
  </div>
</template>

<script>
import { getValidationCode } from "src/service/account";
import { checkPhoneIllegal } from "src/config/mUtils";
import { VALIDATION_TYPE } from "src/constant/account.js";

export default {
  data() {
    return {
      phoneNumber: null,
      imgCode: null,
      smsCode: null,
      tokenId: null,
      imgPrefix: "data:image/jpeg;base64,",
      authImg: null,
      computedTime: null
    }
  },

  props: ['needWhat'],

  methods: {
    clearInput(field) {
      switch(field) {
        case 'phoneNumber':
          this.phoneNumber = null;
          break;
        case 'imgCode':
          this.imgCode = null;
          break;
        case 'smsCode':
          this.smsCode = null;
          break;
        default:
          break;
      }
    },
    async getImgCode() {
      if (!this.rightPhoneNumber) {
        this.$toast.text("请输入正确的手机号");
        return;
      }
      let imgResult = await getValidationCode(this.phoneNumber,VALIDATION_TYPE.IMG_CODE,null,null,null);
    }
  },

  computed: {
    rightPhoneNumber: function() {
      return checkPhoneIllegal(this.phoneNumber);
    }
  }
};
</script>

<style lang="scss" scoped>
@import "src/style/mixin";

.validate_container {
  display: flex;
  flex-direction: column;
  background-color: #ffffff;
  text-align: center;
  .validate_form {
    margin-top: 0.7rem;
    .input_container {
      display: inline-flex;
      border: 0.05rem solid #f2f2f2;
      border-radius: 0.1rem;
      margin-top: 0.25rem;
      width: 70%;
      height: 2rem;
      .image_in_input {
        width: 15%;
        height: 100%;
        display: inline-block;
        svg {
          @include wh(38%, 100%);
        }
        .s_svg {
          @include wh(35%, 100%);
        }
      }
      input {
        @include sc(0.6rem, #444444);
      }
      .phone_input{
        width: 70%;
      }
      .img_code_input {
        width: 45%;
      }
      .sms_code_input {
        width: 40%;
      }
      .img_code_get {
        border-radius: 0.1rem;
        background-color: #fff;
        height: 100%;
        width: 40%;
        display: inline-block;
        .btn_txt {
          @include sc($fontSize24, #999999);
          width: 10%;
          text-align: left;
          vertical-align: middle;
          margin-left: -5px;
        }
        svg {
          @include wh(15%, 100%);
          vertical-align: middle;
        }
      }
      .sms_code_get {
        @include sc(0.6rem, #ffffff);
        border-radius: 0.1rem;
        background-image: linear-gradient(to left, #63faf2, #35ef9d);
        height: 100%;
        width: 32%;
      }
      .sms_code_get:disabled {
        opacity: 0.5;
      }
    }
    // .hint_container {
    //   @include sc($fontSize26, #999999);
    //   width: 70%;
    //   display: inline-flex;
    //   .phone_hint {
    //     color: #4fe0a1;
    //   }
    // }
  }
  .btn_container {
    margin-top: 0.8rem;
    margin-bottom: 0.8rem;
    .go_next_btn {
      display: inline-flex;
      @include sc(0.6rem, #fff);
      justify-content: center;
      background-image: linear-gradient(to left, #63faf2, #35ef9d);     
      border-radius: 0.15rem;
      width: 70%;
      height: 2rem;
    }
    .go_next_btn:disabled {
      opacity: 0.5;
    }
  }
}
</style>
